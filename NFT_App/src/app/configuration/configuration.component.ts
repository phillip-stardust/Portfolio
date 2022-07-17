import { Component, OnInit, TemplateRef, ViewChild } from '@angular/core';
import { NgbModal } from '@ng-bootstrap/ng-bootstrap';
import { NftService } from '../nft.service';
import { ConfigurationMillis } from './configuration-milis.model';
import { Configuration } from './configuration.model';

@Component({
  selector: 'app-configuration',
  templateUrl: './configuration.component.html',
  styleUrls: ['./configuration.component.css'],
  providers: [NftService],
})
export class ConfigurationComponent implements OnInit {
  @ViewChild('savedModal')
  private savedModal!: TemplateRef<Object>;
  public configModel:any;
  public info = '';

  constructor(private nftService: NftService, private modalService: NgbModal) {
    this.configModel = new Configuration(2, 2, 2, 2);
  }

  ngOnInit(): void {
    this.nftService.getConfig().subscribe((config: ConfigurationMillis) => {
      const intervalo = this.parseMillis(config.intervalo);
      const duracion = this.parseMillis(config.duracion);
      this.configModel = new Configuration(intervalo.hours, intervalo.minutes, duracion.hours, duracion.minutes);
    });
  }

  saveConfig(){
    const intervalo = this.parseTime(this.configModel.horasInter, this.configModel.minInter);
    const duracion = this.parseTime(this.configModel.horasDur, this.configModel.minDur);
    this.nftService.setConfig(new ConfigurationMillis(intervalo, duracion)).subscribe((res) => {
      if(res) {
        this.info = 'Configuración guardada exitosamente!';
        this.modalService.open(this.savedModal);
      }
    }, (err) =>{
      this.info = "Ocurrió un error al guardar la configuración, intenta más tarde.";
      this.modalService.open(this.savedModal);
    });
  }

  parseMillis(millis: number) {
    const minutes = parseInt(((millis / (1000 * 60)) % 60 ).toFixed(1));
    const hours = parseInt(((millis / (1000 * 60)) / 60).toFixed(1));
    
    return {
      'hours': hours, 
      'minutes': minutes
    };
  }
  
  parseTime(hours: number, minutes: number) {
    const millis = (hours * 60 * 60 *1000) + (minutes * 60 *1000);
    return millis;
  }
}
