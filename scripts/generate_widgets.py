import json
import os
import argparse

def load_template(template_name):
    """
    Carga una plantilla desde la carpeta templates.
    """
    templates_dir = os.path.join(os.path.dirname(__file__), "templates")
    template_path = os.path.join(templates_dir, template_name)
    with open(template_path, "r", encoding="utf-8") as template_file:
        return template_file.read()

def parse_json(json_file):
    """
    Carga y parsea el archivo JSON con la configuración del widget.
    """
    with open(json_file, "r", encoding="utf-8") as file:
        return json.load(file)

def generate_widget(json_data):
    """
    Genera los archivos .h y .cpp basados en la configuración JSON y las plantillas.
    """
    widget_name = json_data["widget"]
    parameters = json_data["parameters"]

    # Conjuntos para eliminar redundancias
    forward_classes = {param["qt_type"] for param in parameters}
    forward_classes.add("QLabel")
    include_headers = {param["qt_type"] for param in parameters}
    include_headers.add("QLabel")  # Incluir QLabel
    
    # Procesar las declaraciones y el código basado en los parámetros
    forward_declaration = "\n".join(f"class {cls};" for cls in sorted(forward_classes))
    
    data_members = "\n".join(
        [
            f"    QLabel *mLabel{param['name'].capitalize()};"
            for param in parameters
            if param["qt_type"] not in {"QCheckBox", "QRadioButton"}
        ] + [
            f"    {param['qt_type']} *m{param['name'].capitalize()};"
            for param in parameters
        ]
    )
    init_ui = "\n".join(
        [
            f"    mLabel{param['name'].capitalize()} = new QLabel(this);\n"
            f"    gridLayout->addWidget(mLabel{param['name'].capitalize()}, {index}, 0);\n"
            f"    m{param['name'].capitalize()} = new {param['qt_type']}(this);\n"
            f"    gridLayout->addWidget(m{param['name'].capitalize()}, {index}, 1);"
            if param["qt_type"] not in {"QCheckBox", "QRadioButton"}
            else f"    m{param['name'].capitalize()} = new {param['qt_type']}(this);\n"
            f"    gridLayout->addWidget(m{param['name'].capitalize()}, {index}, 0, 1, 2);"
            for index, param in enumerate(parameters)
        ]
    )
    for param in json_data["parameters"]:
        # Manejo específico para QComboBox
        if param["qt_type"] == "QComboBox":
            values = param.get("values", [])
            if values:
                # Añadir opciones al QComboBox
                combo_values = "\n".join(
                    [f'm{param["name"].capitalize()}->addItem("{value}");' for value in values]
                )
                init_ui += f"\n{combo_values}"
            # Configuración de valor predeterminado
            if param.get("def_value"):
                init_ui += f'\nm{param["name"].capitalize()}->setCurrentText("{param["def_value"]}");'
        
        # Manejo para QSpinBox y QDoubleSpinBox
        elif param["qt_type"] in {"QSpinBox", "QDoubleSpinBox"}:
            if "min_value" in param:
                init_ui += f'\nm{param["name"].capitalize()}->setMinimum({param["min_value"]});'
            if "max_value" in param:
                init_ui += f'\nm{param["name"].capitalize()}->setMaximum({param["max_value"]});'
            # Configuración de valor predeterminado
            if param.get("def_value"):
                init_ui += f'\nm{param["name"].capitalize()}->setValue({param["def_value"]});'
            
    connect_signals_and_slots = "\n".join(
        [
            f"    connect(m{param['name'].capitalize()}, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &{widget_name}Widget::update);"
            if param["qt_type"] == "QDoubleSpinBox"
            else f"    connect(m{param['name'].capitalize()}, QOverload<int>::of(&QSpinBox::valueChanged), this, &{widget_name}Widget::update);"
            if param["qt_type"] == "QSpinBox"
            else f"    connect(m{param['name'].capitalize()}, &QLineEdit::textChanged, this, &{widget_name}Widget::update);"
            if param["qt_type"] == "QLineEdit"
            else f"    connect(m{param['name'].capitalize()}, &QComboBox::currentTextChanged, this, &{widget_name}Widget::update);"
            if param["qt_type"] == "QComboBox"
            else f"    // No signal connected for {param['qt_type']}, unsupported type"
            for param in parameters
            if param["qt_type"] not in {"QCheckBox", "QRadioButton"}  # Estos no necesitan señales.
        ]
    )
    translate_text = "\n".join(
        [
            f"    mLabel{param['name'].capitalize()}->setText(QApplication::translate(\"{widget_name}Widget\", \"{param['text']}\", nullptr));"
            if param["qt_type"] not in {"QCheckBox", "QRadioButton"}
            else f"    m{param['name'].capitalize()}->setText(QApplication::translate(\"{widget_name}Widget\", \"{param['text']}\", nullptr));"
            for param in parameters
        ]
    )

    # Conjunto de tipos básicos que no requieren referencias constantes
    basic_types = {"int", "double", "float", "bool"}
    
    # Función auxiliar para determinar métodos de acceso
    def get_accessor(param):
        if param["qt_type"] == "QDoubleSpinBox":
            return "value", "setValue"
        elif param["qt_type"] == "QSpinBox":
            return "value", "setValue"
        elif param["qt_type"] == "QLineEdit":
            return "text", "setText"
        elif param["qt_type"] == "QComboBox":
            return "currentText", "setCurrentText"
        elif param["qt_type"] == "QRadioButton":
            return "isChecked", "setChecked"
        elif param["qt_type"] == "QCheckBox":
            return "isChecked", "setChecked"
        else:
            raise ValueError(f"Tipo de widget no soportado: {param['qt_type']}")
            
    # Generar getters y setters
    getters = "\n".join(
        [f"    {param['type']} {param['name']}() const;" for param in parameters]
    )
    setters = "\n".join(
        [
            f"    void set{param['name'].capitalize()}({param['type']} value);"
            if param["type"] in basic_types
            else f"    void set{param['name'].capitalize()}(const {param['type']}& value);"
            for param in parameters
        ]
    )

    getters_impl = "\n".join(
        [
            f"{param['type']} {widget_name}Widget::{param['name']}() const\n"
            f"{{\n    return m{param['name'].capitalize()}->{get_accessor(param)[0]}();\n}}"
            for param in parameters
        ]
    )
    setters_impl = "\n".join(
        [
            f"void {widget_name}Widget::set{param['name'].capitalize()}({param['type']} value)\n"
            f"{{\n    m{param['name'].capitalize()}->{get_accessor(param)[1]}(value);\n}}"
            if param["type"] in basic_types
            else f"void {widget_name}Widget::set{param['name'].capitalize()}(const {param['type']}& value)\n"
            f"{{\n    m{param['name'].capitalize()}->{get_accessor(param)[1]}(value);\n}}"
            for param in parameters
        ]
    )
    # Generar el método clear()
    clear_method = "\n".join(
        [
            f"    m{param['name'].capitalize()}->{get_accessor(param)[1]}({param.get('def_value', '0')});"
            if param["type"] in basic_types
            else f"    m{param['name'].capitalize()}->{get_accessor(param)[1]}(\"{param.get('def_value', '')}\");"
            for param in parameters
        ]
    )

    # Cargar las plantillas
    header_template = load_template("widget_template.h")
    cpp_template = load_template("widget_template.cpp")

    # Sustituir los marcadores en las plantillas
    header_content = header_template.format(
        Name=widget_name,
        forward_declaration=forward_declaration,
        dataMembers=data_members,
        getter=getters,
        setter=setters        
    )
    cpp_content = cpp_template.format(
        Name=widget_name,
        ComponentName=widget_name,
        includes="\n".join(f"#include <{cls}>" for cls in sorted(include_headers)),
        init_ui=init_ui,
        connect_signals_and_slots=connect_signals_and_slots,
        translate_text=translate_text,
        clear_code=clear_method,
        getter=getters_impl,
        setter=setters_impl        
    )

    # Crear la carpeta de salida
    os.makedirs("output", exist_ok=True)
    header_path = os.path.join("output", f"{widget_name}Widget.h")
    cpp_path = os.path.join("output", f"{widget_name}Widget.cpp")

    # Escribir los archivos generados
    with open(header_path, "w", encoding="utf-8") as header_file:
        header_file.write(header_content)
    with open(cpp_path, "w", encoding="utf-8") as cpp_file:
        cpp_file.write(cpp_content)

    print(f"Generado: {header_path} y {cpp_path}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generador de widgets basados en JSON y plantillas"
    )
    parser.add_argument(
        "config_file",
        type=str,
        help="Ruta al archivo JSON con la configuración del widget"
    )
    args = parser.parse_args()

    # Leer configuración y generar widgets
    json_data = parse_json(args.config_file)
    generate_widget(json_data)
