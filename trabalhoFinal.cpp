#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


struct paciente{
     string senha;
     char prioridade;
     int hora;
     int minuto;
     int horaAtendimento;
     int minutoAtendimento;
};

int main(){

     queue<string> emergencia;
     queue<string> urgencia;
     queue<string> poucoUrgente;
     queue<string> naoUrgente;

     int horaSemAtendimento;
     int minutoSemAtendimento;

     int atendidos = 0;


     paciente informacoes;

     char escolha;

     while(true){
     cout << "Digite: C - Para cadastrar um paciente, \n A - Para atendimento, \n D - Exibir informações \n Q - Para Sair" << endl;
     cin >> escolha;

     if(escolha == 'C'){
               cout << "Digite a senha: \n";
               cin >> informacoes.senha;

               cout << "Digite o tipo da atendimento: \n V - Emergência \n A - Urgência \n D - Pouco Urgente \n B - Não Urgente  \n";
               cin >> informacoes.prioridade;

               cout << "Digite a hora: \n";
               cin >> informacoes.hora;

               cout << "Digite o minuto: \n";
               cin >> informacoes.minuto;

               if(informacoes.prioridade == 'V'){
                    emergencia.push(informacoes.senha);
               }else if(informacoes.prioridade == 'A'){
                    urgencia.push(informacoes.senha);
               }else if(informacoes.prioridade == 'D'){
                    poucoUrgente.push(informacoes.senha);
               }
               else if(informacoes.prioridade == 'B'){
                    naoUrgente.push(informacoes.senha);
               }
     }else if(escolha == 'A'){
          //  cout << "Digite a hora do atendimento: \n";
          //      cin >> ;
          // cout << "Digite o minuto do atendimento: \n";
          // cin >> ;
               if(!emergencia.empty()||!urgencia.empty() ||!poucoUrgente.empty() || !naoUrgente.empty() ){
                    if(!emergencia.empty()){
                         emergencia.pop();

                         atendidos ++;

                    }else if(!urgencia.empty()){
                         urgencia.pop();

                         atendidos ++;


                    }else if(!poucoUrgente.empty()){
                         poucoUrgente.pop();

                         atendidos ++;

                    }else if(!naoUrgente.empty()){
                         naoUrgente.pop();

                         atendidos ++;

                    }
                    //V:0 A:1 D:0 B:1 | Atendidos:1
                    cout << "V: " << emergencia.size() << " A: " <<  urgencia.size() << " D: " <<  poucoUrgente.size() << " B: "  ;
               }else{
               cout << "Sem pacientes aguardando atendimento";
               
          }
          }else if(escolha == 'D'){
               // --- RELATÓRIO FINAL ---
               //      Total atendidos: 3
               //      Por prioridade: V=1 A=2 D=0 B=0
               //      Pico de lotação: 3
               //      Espera máxima: 10 min
               cout << " Total atendidos: ";
          }
     }

     return 0;
}