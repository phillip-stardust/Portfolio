import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HomeComponent } from './home/home.component';
import { ProfileComponent } from './profile/profile.component';
import { SensorComponent } from './sensor/sensor.component';
import { ParameterGroupComponent } from './parameter-group/parameter-group.component';
import { SwitchComponent } from './switch/switch.component';
import { NgbModule } from '@ng-bootstrap/ng-bootstrap';
import { ConfigurationComponent } from './configuration/configuration.component';
import { FormsModule } from '@angular/forms';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    ProfileComponent,
    SensorComponent,
    ParameterGroupComponent,
    SwitchComponent,
    ConfigurationComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    NgbModule, 
    HttpClientModule,
    FormsModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
