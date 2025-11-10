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

void verificarLotacao(queue<paciente> &emergencia, queue<paciente> &urgencia, queue<paciente> &poucoUrgente, queue<paciente> &naoUrgente, int &lotacao)
{
     int soma = 0;
     soma = emergencia.size() + urgencia.size() + poucoUrgente.size() + naoUrgente.size();
     if (lotacao < soma)
     {
          lotacao = soma;
     }
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
     int lotacao = 0;

     paciente informacoes;

     char escolha;

     int atendidosEmergencia = 0, atendidosUrgencia = 0, atendidosPoucoUrgente = 0, atendidosNaoUrgente = 0;

     while (true)
     {
          // cout << " \n Digite: \n C - Para cadastrar um paciente, \n A - Para atendimento, \n D - Exibir informações \n Q - Para Sair" << endl;
          cin >> escolha;

          switch (escolha)
          {
          case 'C':
          {    // IMPORTANTE: perguntar para o professor qual vai ser a forma de teste
               // cout << "Digite a senha, o tipo da atendimento: \n V - Emergência \n A - Urgência \n D - Pouco Urgente \n B - Não Urgente \n a hora e o o minuto: \n ";
               cin >> informacoes.senha >> informacoes.prioridade >> informacoes.hora >> informacoes.minuto;

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
               // cout << "Digite a hora do atendimento: \n";
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

               // V:0 A:1 D:0 B:1 | Atendidos:1
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
               cout << "Total atendidos: " << atendidos.size() << "\n"; //ok
               cout << "Por prioridade: V: " << atendidosEmergencia << " A: " << atendidosUrgencia << " D: " << atendidosPoucoUrgente << " B: " << atendidosNaoUrgente << endl;
               cout << "Pico de lotação: " << lotacao << "\n"; // ok
               cout << "Espera máxima: " << esperaMaxima << " min"; //ok
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