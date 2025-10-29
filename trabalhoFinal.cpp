#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct paciente
{
     string senha;
     char prioridade;
     int hora;
     int minuto;
     int horaAtendimento;
     int minutoAtendimento;
     int tempoEspera;
};

void atenderPaciente(queue<paciente> &fila, vector<paciente> &atendidos, int horaChamada, int minutoChamada)
{
     paciente atendido = fila.front(); // armazena primeiro paciente da fila que foi atendido
     fila.pop();

     atendido.horaAtendimento = horaChamada;
     atendido.minutoAtendimento = minutoChamada;

     int tempoEsperado = ((horaChamada / 60) + minutoChamada) - ((atendido.hora / 60) + atendido.minuto);

     atendido.tempoEspera = tempoEsperado;

     atendidos.push_back(atendido);
}

int main()
{
     vector<paciente> atendidos; // vetor com todos pacientes atendidos

     queue<paciente> emergencia;
     queue<paciente> urgencia;
     queue<paciente> poucoUrgente;
     queue<paciente> naoUrgente;

     int horaChamada;
     int minutoChamada;

     paciente informacoes;

     char escolha;

     while (true)
     {
          cout << "Digite: C - Para cadastrar um paciente, \n A - Para atendimento, \n D - Exibir informações \n Q - Para Sair" << endl;
          cin >> escolha;

          switch (escolha)
          {
          case 'C':
               cout << "Digite a senha: \n";
               cin >> informacoes.senha;

               cout << "Digite o tipo da atendimento: \n V - Emergência \n A - Urgência \n D - Pouco Urgente \n B - Não Urgente  \n";
               cin >> informacoes.prioridade;

               cout << "Digite a hora: \n";
               cin >> informacoes.hora;

               cout << "Digite o minuto: \n";
               cin >> informacoes.minuto;

               switch (informacoes.prioridade)
               {
               case 'V':
                    emergencia.push(informacoes);
                    break;
               case 'A':
                    urgencia.push(informacoes);
                    break;
               case 'D':
                    poucoUrgente.push(informacoes);
                    break;
               case 'B':
                    naoUrgente.push(informacoes);
                    break;
               }
               break;
          case 'A':
               cout << "Digite a hora do atendimento: \n";
               cin >> horaChamada;
               cout << "Digite o minuto do atendimento: \n";
               cin >> minutoChamada;

               if (!emergencia.empty())
               {
                    atenderPaciente(emergencia, atendidos, horaChamada, minutoChamada);
               }
               else if (!urgencia.empty())
               {
                    atenderPaciente(urgencia, atendidos, horaChamada, minutoChamada);
               }
               else if (!poucoUrgente.empty())
               {
                    atenderPaciente(poucoUrgente, atendidos, horaChamada, minutoChamada);
               }
               else if (!naoUrgente.empty())
               {
                    atenderPaciente(naoUrgente, atendidos, horaChamada, minutoChamada);
               }
               else
               {
                    cout << horaChamada << minutoChamada;
                    cout << "Sem pacientes aguardando atendimento";
               }
               break;
          case 'D':

               // V:0 A:1 D:0 B:1 | Atendidos:1
               cout << "V: " << emergencia.size() << " A: " << urgencia.size() << " D: " << poucoUrgente.size() << " B: " << naoUrgente.size() << " | Atendidos: " << atendidos.size();
               break;

          case 'Q':
               // --- RELATÓRIO FINAL ---
               //      Total atendidos: 3
               //      Por prioridade: V=1 A=2 D=0 B=0
               //      Pico de lotação: 3
               //      Espera máxima: 10 min

               int atendidosEmergencia, atendidosUrgencia, atendidosPoucoUrgente, atendidosNaoUrgente;

               for (int i = 0; i < atendidos.size(); i++)
               {
                    switch (atendidos[i].prioridade)
                    {
                    case 'V':
                         atendidosEmergencia++;
                         break;
                    case 'A':
                         atendidosUrgencia++;
                         break;
                    case 'D':
                         atendidosPoucoUrgente++;
                         break;
                    case 'B':
                         atendidosNaoUrgente++;
                         break;
                    default:
                         break;
                    }
               }

               int esperaMaxima = 0;

               for (int i = 1; i < atendidos.size(); i++)
               {
                    esperaMaxima = atendidos[0].tempoEspera;
                    if (esperaMaxima < atendidos[i].tempoEspera)
                    {
                         esperaMaxima = atendidos[i].tempoEspera;
                    }
               }

               // Fazer o claculo de transformar horas em minutos e depois somar os minutos de entreda de cadastro e subtrair com chamada
               cout << "-- Relatório Final -- \n";
               cout << " Total atendidos: " << atendidos.size();
               cout << " Por prioridade: V =" << atendidosEmergencia << " A: " << atendidosUrgencia << "D: " << atendidosPoucoUrgente << " B: " << atendidosNaoUrgente << endl;
               cout << "Pico de lotação: "; // Toda vez que adicionar ou atender um paciente verifica se é maior que o pico de lotação e atualiza o valor somando todas as filas
               cout << "Espera máxima: " << esperaMaxima;
               break;

          default:
               cout << "Escolha Inválida!";
          }
     }
     return 0;
}