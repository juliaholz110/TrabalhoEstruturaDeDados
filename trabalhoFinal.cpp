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
     paciente atendido = fila.front();
     fila.pop();

     atendido.horaAtendimento = horaChamada;
     atendido.minutoAtendimento = minutoChamada;

     int tempoEsperado = (horaChamada * 60 + minutoChamada) - (atendido.hora * 60 + atendido.minuto);

     atendido.tempoEspera = tempoEsperado;

     atendidos.push_back(atendido);
}

int verificarLotacao(queue<paciente> &emergencia, queue<paciente> &urgencia, queue<paciente> &poucoUrgente, queue<paciente> &naoUrgente, int &lotacao)
{
     int soma = 0;
     soma = emergencia.size() + urgencia.size() + poucoUrgente.size() + naoUrgente.size();
     if (lotacao < soma)
     {
          lotacao = soma;
     }
     return lotacao;
}

int main()
{
     vector<paciente> atendidos;

     queue<paciente> emergencia;
     queue<paciente> urgencia;
     queue<paciente> poucoUrgente;
     queue<paciente> naoUrgente;

     int horaChamada;
     int minutoChamada;
     int lotacao = 0;
     int esperaMaxima = 0;

     paciente informacoes;

     char escolha;

     int atendidosEmergencia = 0, atendidosUrgencia = 0, atendidosPoucoUrgente = 0, atendidosNaoUrgente = 0;

     while (true)
     {
          cout << " \n Digite: \n C - Para cadastrar um paciente, \n A - Para atendimento, \n D - Exibir informações \n Q - Para Sair" << endl;
          cin >> escolha;

          switch (escolha)
          {
          case 'C':
          {
               cout << "Digite a senha: \n";
               cin >> informacoes.senha;

               cout << "Digite o tipo da atendimento: \n V - Emergência \n A - Urgência \n D - Pouco Urgente \n B - Não Urgente \n";
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
               verificarLotacao(emergencia, urgencia, poucoUrgente, naoUrgente, lotacao);
               break;
          }
          case 'A':
          {
               cout << "Digite a hora e os minutos do atendimento: \n";
               cin >> horaChamada >> minutoChamada;

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
                    if (horaChamada < 10)
                         cout << "0";
                    cout << horaChamada << " ";

                    if (minutoChamada < 10)
                         cout << "0";
                    cout << minutoChamada;
                    cout << " Sem pacientes aguardando atendimento";
               }
               break;
          }
          case 'D':

               cout << "V: " << emergencia.size() << " A: " << urgencia.size() << " D: " << poucoUrgente.size() << " B: " << naoUrgente.size() << " | Atendidos: " << atendidos.size() << "\n";
               break;

          case 'Q':
          {
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

               if (!atendidos.empty())
               {
                    esperaMaxima = atendidos[0].tempoEspera;
                    for (int i = 1; i < atendidos.size(); i++)
                    {
                         if (atendidos[i].tempoEspera > esperaMaxima)
                         {
                              esperaMaxima = atendidos[i].tempoEspera;
                         }
                    }
               }

               cout << "-- Relatório Final -- \n";
               cout << "Total atendidos: " << atendidos.size() << "\n";
               cout << "Por prioridade: V: " << atendidosEmergencia << " A: " << atendidosUrgencia << " D: " << atendidosPoucoUrgente << " B: " << atendidosNaoUrgente << endl;
               cout << "Pico de lotação: " << lotacao << "\n";
               cout << "Espera máxima: " << esperaMaxima << " min";
               return 0;
               break;
          }

          default:
          {
               cout << "Escolha Inválida!";
               break;
          }
          }
     }
     return 0;
}