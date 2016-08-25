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
public class Servicio {
    
    
    
    private int servicio;
    private long demora;

    public Servicio() {
        this.servicio = -1;
        this.demora = -1;
    }

    public Servicio(int servicio) {
        this.servicio = servicio;
        demora = (servicio+1)*15;
    }

    public int getServicio() {
        return servicio;
    }

    public void setServicio(int servicio) {
        this.servicio = servicio;
    }

    public float getDemora() {
        return demora;
    }

    public void setDemora(long demora) {
        this.demora = demora;
    }

    @Override
    public String toString() {
        return "Servicio{" + "servicio=" + servicio + ", demora=" + demora + '}';
    }
    
    
    
}
