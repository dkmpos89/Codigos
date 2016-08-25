/*
 * Copyright (C) 2015 cesar bustamante
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * afloat with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * Programa que simula el proceso en una cola de bancos
 * @author: Cesar Bustamante estudiante Ing. Civil Informatica UCM, Ayudantia Estructuras de datos
 * @version: version 1.0
 * @see <a href = "http://docs.oracle.com/javase/7/docs/" /> Para mayor informacion acerca de java 7 </a>

 */
package banco;

import java.util.ArrayList;//arreglo dinamico de java
import java.util.LinkedList;//Lista enlazada de java
import java.util.Queue;//Cola en java
import java.util.Random;//para generar numeros aleatorios
import java.util.Scanner;//para leer del teclado

/**
 *
 * @author hduser
 */
public class Banco {

   
/*
    private enum tipoCuenta{
        corriente,ahorro,vista,nulo;
    }
    
    private enum tipoServicio{
        deposito,giro,ambos,otro,no;
    }
    */
    
    public static void main(String[] args) {
        
        int n;//cantidad de clientes
        Queue<Cliente> cola;
        ArrayList<Queue> list=new ArrayList<>();
        Scanner s=new Scanner(System.in);//variable scaner para leer desde el teclado
        System.out.println("Ingresa la cantidad de clientes :)");
        n=s.nextInt();
        cola = ingresarClientes(n);
        list=comienzaSimulacion(cola);
        estadisticas(list,n);
        System.exit(0);
        
    }
    
    
    private static Queue ingresarClientes(int n){
        
        Random r=new Random();
        Queue<Cliente> cola;//crea variable cola
        cola = new LinkedList();//iciacializa la cola (constructor de lista enlazada)
        for (int i = 0; i < n; i++) {
            Servicio s=new Servicio(r.nextInt(5));
            //System.out.println("serv "+s.toString());
            Cliente cl=new Cliente( r.nextInt(4), r.nextFloat(), s);
            cola.add(cl);
            //System.out.println("cl "+cl.toString());
        }
        
        return cola;
        
    }
    
    private static ArrayList<Queue> comienzaSimulacion(Queue<Cliente> colaEspera){
        
        ArrayList <Queue> list=new ArrayList<>();
        float demora = 0,max=0;
        Queue<Cliente> colaAtendidos,colaAbandona;//crea variables cola
        colaAtendidos = new LinkedList();//iciacializa la cola (constructor de lista enlazada)
        colaAbandona = new LinkedList();//iciacializa la cola (constructor de lista enlazada)
        //mientras la cola no este vacia
        while(colaEspera.peek()!=null){
            demora+=colaEspera.peek().servicio.getDemora();//se almacena la demora de cada cliente      
            max=colaEspera.peek().getTiempoMax();//maximo del cliente actual
            Cliente cl=colaEspera.remove();
            //seteamos su variable de tiempo de espera
            cl.setTiempoEspera(demora);
            //si la demora es menor que el tiempo max se agrega a atendidos sino a abandona
            if(demora <= max){
                colaAtendidos.add(cl); 
            }else{
                colaAbandona.add(cl);
            }
        }
        
        list.add(colaAtendidos);
        list.add(colaAbandona);
        
        return list;//retorna ambas listas
    }

    
    //calcula las estadisticas solicitadas
    private static void estadisticas(ArrayList<Queue> list, int n) {
        stadisticas s=new stadisticas();
        s=stats(list.get(0), list.get(1),s ,n);

        System.out.println("Sistema de analisis de datos");
        System.out.println("De un total de "+n+" clientes en la cola");
        System.out.println(n-list.get(1).size()+" fueron atendidos satisfactoriamente ");
        System.out.println(list.get(1).size()+" abandonaron la cola");
        System.out.println("El promedio de espera fue "+(s.getMedia()/(list.get(0).size()) )+" segundos");
        System.out.println("El % de clientes por cada cuenta fue: ");
        System.out.println("Cuenta corriente "+(s.corriente*100)/n+"%");
        System.out.println("Cuenta ahorro "+(s.ahorro*100)/n+"%");
        System.out.println("Cuenta vista "+(s.vista*100)/n+"%");
        System.out.println("Cuenta nulo "+(s.nulo*100)/n+"%");
        System.out.println("El % de clientes por cada servicio fue: ");
        System.out.println("Cuenta deposito "+(s.deposito*100)/n+"%");
        System.out.println("Cuenta giro "+(s.giro*100)/n+"%");
        System.out.println("Cuenta ambos "+(s.ambos*100)/n+"%");
        System.out.println("Otro tipo de servicio "+(s.otro*100)/n+"%");
        System.out.println("No posee cuenta "+(s.no*100)/n+"%");
        
    }
    
    
    private static stadisticas stats(Queue<Cliente> colaAtendidos,Queue<Cliente> colaAbandona, stadisticas s,int n){ 
        
        System.out.println("Clientes Atendidos");
        //estadisticas para los que fueron atendidos
        for (int i = 0; i < colaAtendidos.size(); i++){
            s.statMedia(colaAtendidos.peek());
            s.statCuentas(colaAtendidos.peek());
            s.statServ(colaAtendidos.peek());
            //muestra clientes atendidos
            System.out.println(colaAtendidos.peek().toString());
            colaAtendidos.add(colaAtendidos.remove());
        }
        System.out.println("Clientes que abandonaron la cola");
        //stadisticas para los q abandonaron
        for (int i = 0; i < colaAbandona.size(); i++){
            //s.statMedia(colaAbandona.peek());
            s.statCuentas(colaAbandona.peek());
            s.statServ(colaAbandona.peek());
            //muestra clientes q abandonaron
            System.out.println(colaAbandona.peek().toString());
            colaAbandona.add(colaAbandona.remove());
        }

        return s;
    }

}
