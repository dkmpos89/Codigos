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
package banco;

/**
 *
 * @author cesar
 */
public class Cliente {
    
    
    
    private int cuenta;
    private float tiempoMax;
    private float tiempoEspera;
    Servicio servicio;

    public Cliente() {
        this.cuenta = -1;
        this.tiempoMax = -1;
        this.tiempoEspera = -1;
        this.servicio=null;
    }

    public Cliente(int cuenta, float tiempoMax,Servicio servicio) {
        this.cuenta = cuenta;
        this.tiempoMax = tiempoMax*500 +700;
        this.tiempoEspera = 0;
        this.servicio=servicio;
    }

    public int getCuenta() {
        return cuenta;
    }

    public void setCuenta(int cuenta) {
        this.cuenta = cuenta;
    }
    
    
    public Servicio getServicio() {
        return servicio;
    }

    public void setServicio(Servicio s) {
        servicio=s;
    }

    public float getTiempoMax() {
        return tiempoMax;
    }

    public void setTiempoMax(float tiempoMax) {
        this.tiempoMax = tiempoMax;
    }

    public float getTiempoEspera() {
        return tiempoEspera;
    }

    public void setTiempoEspera(float tiempoEspera) {
        this.tiempoEspera = tiempoEspera;
    }

    @Override
    public String toString() {
        return "Cliente{" + "cuenta=" + cuenta + ", tiempoMax=" + tiempoMax + ", tiempoEspera=" + tiempoEspera + " " + servicio.toString() + '}';
    }
    
    
    
    
}
