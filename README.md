# EQM - Energy Monitor Quality (Monitor de Qualidade de Energia)


![Visão 3D do protótipo do EQM.](https://github.com/gabriel-laurindo-1/monitorQEE/blob/master/EnergyMonitor/images/view3D.PNG)

## Sobre

O EQM é um protótico de baixo custo, desenvolvido com a finalidade de medir os sinais de tensão, corrente elétrica e frequência, a fim de calcular o fator de potência instantâneo no circuito ao qual foi instalado.  
Dessa maneira, seu objetivo é permitir que o consumidor comum possa ter conhecimento de fatores básico da qualidade da energia em sua instalação, como o fator de potência e o valor médio dos sinais de tensão e corrente, e portanto, atestar a qualidade de sua energia elétrica.

---

## Tecnologias utilizadas

- Arduino
- Linguagem C/C++

---

## Lista de componentes

A relação de componentes utilizados pode ser vista na tabela abaixo.

| Item | Quantidade | Referência |    Valor   |
|------|:----------:|:----------:|:----------:|
| 1    |      1     |     C2     |    220uF   |
| 2    |      1     |     C3     |   0.01uF   |
| 3    |      2     |    C4,C5   |    22pF    |
| 4    |      3     |  R1,R9,R10 |     10k    |
| 5    |      3     |  R2,R3,R4  |     1k     |
| 6    |      1     |     R5     |     220    |
| 7    |      1     |     U1     | ATMEGA328P |
| 8    |      1     |     U2     |    LM358   |
| 9    |      1     |     U3     |   74HC386  |
| 10   |      1     |     U4     |   DS3232   |
| 11   |      1     |     U5     |    7805    |
| 12   |      1     |     U6     |    4093    |
| 13   |      1     |     D1     | LED-YELLOW |
| 14   |      1     |     D2     |   1N4148   |
| 15   |      1     |     D3     |   LED-RED  |
| 16   |      1     |     J1     |  TBLOCK-I2 |
| 17   |      1     |     X1     |   CRYSTAL  |


Para baixa a lista de materias, [Clique aqui!](https://github.com/gabriel-laurindo-1/monitorQEE/blob/master/EnergyMonitor/pcb/Bill%20Of%20Materials%20Energy%20Quality%20Monitor.pdf)


---

<center>
Desenvolvido por <a href="https://github.com/gabriel-laurindo-1"> Gabriel Laurindo.</a>
</center>
