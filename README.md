# Trabalho 1 de Sistemas Digitais Embarcados

Nomes: Carlos Ferreira, Milena Fernandes
Disciplina: Sistemas Digitais Embarcados
Data: 22/06/2022

## Descrição dos pinos

* Só é usada a porta GPIOA
* Pinos 7 a 4 são de output: LEDS
* Pino 3 é de input: Botão

## Funcionamento

O programa tem um contador ditando o número do LED que será invertido. 
Cada vez que o botão é pressionado, o LED apontado pelo contador é invertido e o contador é incrementado.

```
contador = 0
1111
```

`APERTA BOTÃO`

```
contador = 1
0111
```

`APERTA BOTÃO`

```
contador = 2
0011
1
```

`APERTA BOTÃO`

```
contador = 3
0001
0
```

`APERTA BOTÃO`

```
contador = 0
0000
1
```

`APERTA BOTÃO`

```
contador = 1
1000
0
```

