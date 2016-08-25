/*
 * Copyright (C) 2015 hduser
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
package banco;

/**
 *
 * @author hduser
 */
public class stadisticas {
    
    float media=0;
    int corriente=0,ahorro=0,vista=0,nulo=0;//cuenta
    int deposito = 0,giro = 0,ambos = 0,otro,no = 0;//servicio

    public stadisticas() {
    }
    
    public  void statCuentas(Cliente cl){
        
        switch ( cl.getCuenta() ){
                    case 0: corriente++;
                            break;
                    case 1: ahorro++;
                            break;
                    case 2: vista++;
                            break;
                    case 3: nulo++;
                            break;
                    default: System.out.println("tipo de cuenta no definida "+cl.getCuenta());
            }
        
    }
    
    public void statServ(Cliente cl){
        
        switch ( cl.getServicio().getServicio() ){
                    case 0: deposito++;
                            break;
                    case 1: giro++;
                            break;
                    case 2: ambos++;
                            break;
                    case 3: otro++;
                            break;
                    case 4: no++;
                            break;
                    default: System.out.println("tipo de servicio no definido "+cl.getServicio().getServicio());
            }
    }
    
    public void statMedia(Cliente cl){
        
        media+=cl.getTiempoEspera();
        
    }

    public float getMedia() {
        return media;
    }

    public int getCorriente() {
        return corriente;
    }

    public int getAhorro() {
        return ahorro;
    }

    public int getVista() {
        return vista;
    }

    public int getNulo() {
        return nulo;
    }

    public int getDeposito() {
        return deposito;
    }

    public int getGiro() {
        return giro;
    }

    public int getAmbos() {
        return ambos;
    }

    public int getOtro() {
        return otro;
    }

    public int getNo() {
        return no;
    }

    @Override
    public String toString() {
        return "stadisticas{" + "media=" + media + ", corriente=" + corriente + ", ahorro=" + ahorro + ", vista=" + vista + ", nulo=" + nulo + ", deposito=" + deposito + ", giro=" + giro + ", ambos=" + ambos + ", otro=" + otro + ", no=" + no + '}';
    }
    
    
    
}
