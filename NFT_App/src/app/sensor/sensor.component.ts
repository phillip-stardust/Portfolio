import { Component, Input, OnInit } from '@angular/core';

@Component({
  selector: 'app-sensor',
  templateUrl: './sensor.component.html',
  styleUrls: ['./sensor.component.css']
})
export class SensorComponent implements OnInit {
  @Input() public sensor: any;
  public min = 0;
  public max = 0;
  public porcentaje = 0;
  public alert = 0;

  constructor() { }

  ngOnInit(): void {

    switch (this.sensor.nombre) {
      case 'Temperatura':
        this.min = 10;
        this.max = 70;
        this.alert = 19;
        break;
      case 'Nivel de pH':
        this.min = 0;
        this.max = 10;
        this.alert = 4;
        break;
      case 'Nivel de agua':
        this.min = 0;
        this.max = 40;
        this.alert = 20 ;
        break;
      case 'humidity':
        this.min = 0;
        this.max = 100;
        break;
      default:
        this.min = 0;
        this.max = 100;
    }
    this.porcentaje = 100 * (this.sensor.valor - this.min) / (this.max - this.min);
    if (this.sensor.valor > this.max) {
      this.porcentaje = 100;
    } else if (this.sensor.valor < this.min) {
      this.porcentaje = 0;
    }
    var type;
    if (this.sensor.valor == this.alert){
      type = 'warning'
    }
  }

}
