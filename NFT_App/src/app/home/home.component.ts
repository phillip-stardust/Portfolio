import { Component, OnInit } from '@angular/core';
import { NftService } from '../nft.service';
import { Sensor } from '../sensor/sensor.model';
import { interval } from 'rxjs';
import { mergeMap, startWith } from 'rxjs/operators';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
  providers: [NftService],
})
export class HomeComponent implements OnInit {
  public sensors: Sensor[] = [];
  public switchs: Sensor[] = [];
  public modoManual = new Sensor();
  public MMchecked = true;
  public cambiandoSwitch = false;

  constructor(private nftService: NftService) {
  }

  ngOnInit(): void {
    this.getSensors();
    this.modoManual.nombre = 'Modo manual';
    this.nftService.getModoManual().subscribe(data => {
      this.MMchecked = data.modoManual;
      this.modoManual.valor = this.MMchecked? 1:0;
    });
  }
  
  getSensors() {
    interval(5000)
    .pipe(
      mergeMap(() => this.nftService.getSensors())
    ).subscribe((sensors: Sensor[]) => {
      if (!this.cambiandoSwitch) {
        this.sensors = [];
        this.switchs = [];
        for (var i = 0; i < 4; i++) {
          this.sensors.push(sensors[i]);
        }
        for (var i = 4; i < 9; i++) {
          this.switchs.push(sensors[i]);
        }
      }
    });
  }

  onChangeMM() {
    this.cambiandoSwitch = true;
    this.nftService.setSwitch(this.modoManual.nombre, this.MMchecked? 0 : 1).subscribe((res) => {
      this.modoManual.valor = this.MMchecked? 0 : 1;
      this.MMchecked = !this.MMchecked;
      this.cambiandoSwitch = false;
    }, (err) =>{
      alert("No se pudo activar el modo manual");
      this.cambiandoSwitch = false;
    });
  }
}

