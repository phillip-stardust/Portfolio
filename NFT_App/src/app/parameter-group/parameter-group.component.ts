import { Component, Input, OnInit } from '@angular/core';

@Component({
  selector: 'app-parameter-group',
  templateUrl: './parameter-group.component.html',
  styleUrls: ['./parameter-group.component.css']
})
export class ParameterGroupComponent implements OnInit {
  @Input() public groupTitle: string = "";
  @Input() public type: string = "sensors";
  @Input() public elements: any;
  @Input() public modoManual: boolean = true;

  constructor() { }

  ngOnInit(): void {
  }

}
