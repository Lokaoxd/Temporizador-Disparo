# 💡 Controle de LEDs com Temporizador e Botão

Este projeto utiliza um Raspberry Pi Pico W para acender e apagar LEDs de maneira controlada por um botão. Quando pressionado, todos os LEDs acendem e, após 3 segundos, começam a apagar um por um, com intervalos de 3 segundos entre cada desligamento.

## 🔧 Como funciona?
- O botão acende todos os LEDs ao ser pressionado.
- Um temporizador `add_alarm_in_ms(3000, turn_off_callback, NULL, false);` inicia a contagem regressiva.
- O callback `turn_off_callback` apaga um LED a cada 3 segundos até que todos estejam apagados.
- Se o botão for pressionado novamente, o processo é reiniciado.

## 📌 Hardware necessário
- Raspberry Pi Pico W
- LEDs (Azul, Vermelho, Verde)
- Resistor (220Ω)
- Botão tátil
- Protoboard e jumpers

## 🛠️ Configuração do Ambiente
### 1️⃣ Instalar o **Visual Studio Code**
- Baixe e instale: [Visual Studio Code](https://code.visualstudio.com/).
- Adicione a extensão [Wokwi](https://marketplace.visualstudio.com/items?itemName=Wokwi.wokwi-vscode).

### 2️⃣ Instalar o **CMake**
- Baixe e instale: [CMake](https://cmake.org/download/).
- Marque **"Add CMake to the system PATH"** na instalação.

### 3️⃣ Instalar o **GCC para ARM**
- Baixe aqui: [GCC ARM Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm).
- Adicione ao `PATH`:
  ```
  C:\Program Files (x86)\Arm GNU Toolchain\<versão>\bin
  ```

### 4️⃣ Instalar o **Pico SDK**
- Baixe aqui: [Pico Setup Windows](https://github.com/raspberrypi/pico-setup-windows).

## 🔌 Testando em um Raspberry Pi Pico
1. Instale o [Zadig](https://zadig.akeo.ie/) para configurar os drivers.
2. Para comunicação serial, instale o [PuTTY](https://www.putty.org/).
3. Compile e faça o upload do código para a placa.

## 📜 Código Principal (resumo)
```c
if (gpio_get(BTN) == 0) {
    gpio_put(led_pin_blue, true);
    gpio_put(led_pin_green, true);
    gpio_put(led_pin_red, true);

    if (alarm_id) cancel_alarm(alarm_id);
    alarm_id = add_alarm_in_ms(3000, turn_off_callback, NULL, false);
}
```
- Se o botão for pressionado, acende todos os LEDs e inicia um **temporizador de 3 segundos**.
- A cada 3 segundos, um LED é apagado até que todos estejam desligados.
