# Sistema de Alarme com Arduino - Modo Dia/Noite
Este projeto consiste em um sistema de alarme inteligente desenvolvido com Arduino UNO, que simula um ambiente doméstico seguro com detecção de intrusão (janela, porta e garagem), modo automático de dia e noite, alerta sonoro com buzzer, iluminação controlada por potenciômetro e interface LCD.

🌙 Principais Funcionalidades:
Modo Dia/Noite Automático: Utiliza um sensor LDR e um potenciômetro para simular a variação de luminosidade ambiente. Quando o ambiente escurece (modo noite), o sistema entra em estado de vigilância e ativa o alarme caso detecte alguma abertura.

Controle de Iluminação: A lâmpada é controlada com um potenciômetro. Quando o sistema é desligado, a lâmpada também é automaticamente desligada.

Interface com LCD (16x2 I2C): Mostra mensagens como "Sistema Ativo", status do modo (dia/noite), e alertas em tempo real caso alguma entrada seja violada.

Botão Geral de Ligar/Desligar: Liga ou desliga todo o sistema, inclusive a iluminação.

LEDs Indicativos e Alarme Sonoro:

LED verde pisca para indicar que o sistema está ativo.

LED vermelho acende quando o alarme é acionado.

Buzzer simula uma sirene policial alternando tons.

🧰 Componentes Utilizados:
1x Arduino UNO

1x Sensor LDR

1x Potenciômetro

3x Botões (porta, janela, garagem)

2x LEDs (verde e vermelho)

1x Buzzer

1x Lâmpada com transistor de controle

1x Módulo LCD I2C 16x2

Resistores, fios e uma protoboard

Fonte externa 9V


![Image](https://github.com/user-attachments/assets/f4932b47-b9d4-4374-9e7a-998bafdfdd35)

![Image](https://github.com/user-attachments/assets/190a439d-ebe3-4bec-a47f-6d0d16db77df)

![Image](https://github.com/user-attachments/assets/475848da-5e38-4668-9d84-047bf35eabdc)
