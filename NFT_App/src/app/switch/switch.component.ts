import { Component, Input, OnInit } from '@angular/core';
import { NftService } from '../nft.service';

@Component({
  selector: 'app-switch',
  templateUrl: './switch.component.html',
  styleUrls: ['./switch.component.css']
})
export class SwitchComponent implements OnInit {
  @Input() public switch: any;
  @Input() public modoManual = true;
  public checked: boolean = false;

  constructor(private nftService: NftService) {}

  ngOnInit(): void {
    this.checked = this.switch.valor === 1? true : false;
  }

  onChange() {
    this.nftService.setSwitch(this.switch.nombre, this.checked? 0 : 1).subscribe((res) => {
      this.switch.valor = this.checked? 0 : 1;
      this.checked = !this.checked;
    }, (err) =>{
      alert("No se pudo cambiar el estado de " + this.switch.nombre);
    });
  }

}
