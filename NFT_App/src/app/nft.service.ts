import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, of } from 'rxjs';
import { ConfigurationMillis } from './configuration/configuration-milis.model';

@Injectable({
  providedIn: 'root'
})
export class NftService {

  constructor(private http: HttpClient) { }

  getSensors(): Observable<any> {
    return this.http.get("/api/sensors");
  }

  getConfig(): Observable<any> {
    return this.http.get('/api/config');
  }

  setConfig(config: ConfigurationMillis): Observable<any> {
    return this.http.post<any>('/api/conf', config);
  }

  setSwitch(sw: string, valor: number): Observable<any> {
    switch (sw) {
      case 'Calentador':
        return this.http.post<any>('/api/calentador', {'valor': valor});
        break;
      case 'Lampara 1':
        return this.http.post<any>('/api/lamp1', {'valor': valor});
        break;
      case 'Lampara 2':
        return this.http.post<any>('/api/lamp2', {'valor': valor});
        break;
      case 'Tanque':
        return this.http.post<any>('/api/tanque', {'valor': valor});
        break;
      case 'Bomba de nutrientes':
        return this.http.post<any>('/api/nutrientes', {'valor': valor});
        break;
      case 'Modo manual':
        return this.http.post<any>('/api/modoManual', {'valor': valor});
        break;
      default:
        return of(null);
        break;
    }
  }

  getModoManual(): Observable<any> {
    return this.http.get('/api/esModoManual');
  }

}
