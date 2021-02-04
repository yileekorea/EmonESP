static const char CONTENT_CONFIG_JS[] PROGMEM = 
  "\"use strict\";function BaseViewModel(e,t,s){void 0===s&&(s={});var n=this;n.remoteUrl=t,ko.mapping.fromJS(e,s,n),n.fetching=ko.observable(!1)}function StatusViewModel(){var e=this;BaseViewModel.call(e,{mode:\"ERR\",wifi_client_connected:0,net_connected:0,srssi:0,ipaddress:\"\",packets_sent:0,packets_success:0,emoncms_connected:0,mqtt_connected:0,free_heap:0,time:\"\",ctrl_mode:\"off\",ctrl_state:0,ota_update:!1},baseEndpoint+\"/status\"),e.isWiFiError=ko.pureComputed(function(){return\"ERR\"===e.mode()}),e.isWifiClient=ko.pureComputed(function(){return\"STA\"==e.mode()||\"STA+AP\"==e.mode()}),e.isWifiAccessPoint=ko.pureComputed(function(){return\"AP\"==e.mode()||\"STA+AP\"==e.mode()}),e.isWired=ko.pureComputed(function(){return\"Wired\"===e.mode()}),e.fullMode=ko.pureComputed(function(){switch(e.mode()){case\"AP\":return\"Access Point (AP)\";case\"STA\":return\"Client (STA)\";case\"STA+AP\":return\"Client + Access Point (STA+AP)\";case\"Wired\":return\"Wired Ethernet\"}return\"Unknown (\"+e.mode()+\")\"})}function ConfigViewModel(){BaseViewModel.call(this,{node_name:\"44smartIO-ESP\",node_description:\"WiFi 55smartIO-ESP Link\",node_type:\"\",ssid:\"\",pass:\"\",emoncms_enabled:!1,emoncms_server:\"data.openevse.com\",emoncms_path:\"/emoncms\",emoncms_apikey:\"\",emoncms_node:\"\",emoncms_fingerprint:\"\",mqtt_enabled:!1,mqtt_server:\"\",mqtt_port:\"\",mqtt_topic:\"\",mqtt_feed_prefix:\"\",mqtt_user:\"\",mqtt_pass:\"\",www_username:\"\",www_password:\"\",espflash:\"\",version:\"0.0.0\",timer_start1:\"\",timer_stop1:\"\",timer_start2:\"\",timer_stop2:\"\",voltage_output:\"\",time_offset:\"\"},baseEndpoint+\"/config\"),this.f_timer_start1=ko.pureComputed({read:function(){return addcolon(this.timer_start1())},write:function(e){this.timer_start1(e.replace(\":\",\"\"))},owner:this}),this.f_timer_stop1=ko.pureComputed({read:function(){return addcolon(this.timer_stop1())},write:function(e){this.timer_stop1(e.replace(\":\",\"\"))},owner:this}),this.f_timer_start2=ko.pureComputed({read:function(){return addcolon(this.timer_start2())},write:function(e){this.timer_start2(e.replace(\":\",\"\"))},owner:this}),this.f_timer_stop2=ko.pureComputed({read:function(){return addcolon(this.timer_stop2())},write:function(e){this.timer_stop2(e.replace(\":\",\"\"))},owner:this}),this.flowT=ko.pureComputed({read:function(){return.0371*this.voltage_output()+7.14},write:function(e){this.voltage_output((e-7.14)/.0371)},owner:this})}function WiFiConfigViewModel(e,t,s,n){var o=this;o.baseEndpoint=e,o.config=t,o.status=s,o.scan=n,o.scanUpdating=ko.observable(!1),o.selectedNet=ko.observable(!1),o.bssid=ko.pureComputed({read:function(){return!1===o.selectedNet()?\"\":o.selectedNet().bssid()},write:function(e){for(var t=0;t<o.scan.results().length;t++){var s=o.scan.results()[t];if(e===s.bssid())return void o.selectedNet(s)}}}),o.select=function(e){o.selectedNet(e)},o.setSsid=function(e){if(!1===o.selectedNet()||e!==o.selectedNet().ssid()){for(var t=0;t<o.scan.filteredResults().length;t++)if(e===(s=o.scan.filteredResults()[t]).ssid())return void o.selectedNet(s);for(var s,t=0;t<o.scan.results().length;t++)if(e===(s=o.scan.results()[t]).ssid())return void o.selectedNet(s);o.selectedNet(!1)}};var i=null,a=!1;o.startScan=function(){o.scanUpdating()||(a=!0,o.scanUpdating(!0),null!==i&&(clearTimeout(i),i=null),o.scan.update(function(){if(a&&(i=setTimeout(o.startScan,3e3)),\"\"===o.bssid())for(var e=o.config.ssid(),t=0;t<o.scan.results().length;t++){var s=o.scan.results()[t];if(e===s.ssid()){o.bssid(s.bssid());break}}o.scanUpdating(!1)}))},o.stopScan=function(){a=!1,o.scanUpdating()||null!==i&&(clearTimeout(i),i=null)},o.enableScan=function(e){e?o.startScan():o.stopScan()},o.forceConfig=ko.observable(!1),o.canConfigure=ko.pureComputed(function(){return!(o.status.isWiFiError()||o.wifiConnecting()||o.status.isWired())&&(!o.status.isWifiClient()||o.forceConfig())}),o.wifiConnecting=ko.observable(!1),o.canConfigure.subscribe(function(e){o.enableScan(e)}),o.status.wifi_client_connected.subscribe(function(e){e&&o.wifiConnecting(!1)}),o.enableScan(o.canConfigure()),o.saveNetworkFetching=ko.observable(!1),o.saveNetworkSuccess=ko.observable(!1),o.saveNetwork=function(){\"\"===o.config.ssid()?alert(\"Please select network\"):(o.saveNetworkFetching(!0),o.saveNetworkSuccess(!1),$.post(o.baseEndpoint()+\"/savenetwork\",{ssid:o.config.ssid(),pass:o.config.pass()},function(){o.status.wifi_client_connected(!1),o.forceConfig(!1),o.wifiConnecting(!0),o.saveNetworkSuccess(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){o.saveNetworkFetching(!1)}))},o.turnOffAccessPointFetching=ko.observable(!1),o.turnOffAccessPointSuccess=ko.observable(!1),o.turnOffAccessPoint=function(){o.turnOffAccessPointFetching(!0),o.turnOffAccessPointSuccess(!1),$.post(o.baseEndpoint()+\"/apoff\",{},function(e){console.log(e),\"\"!==o.status.ipaddress()?setTimeout(function(){window.location=\"//\"+o.status.ipaddress(),o.turnOffAccessPointSuccess(!0)},3e3):o.turnOffAccessPointSuccess(!0)}).fail(function(){alert(\"Failed to turn off Access Point\")}).always(function(){o.turnOffAccessPointFetching(!1)})}}function WiFiScanResultViewModel(e){var t=this;ko.mapping.fromJS(e,{},t),t.strength=ko.computed(function(){var e=t.rssi();return-50<=e?5:-60<=e?4:-67<=e?3:-70<=e?2:-80<=e?1:0})}function WiFiScanViewModel(e){var t=this,s=ko.pureComputed(function(){return e()+\"/scan\"}),n={key:function(e){return ko.utils.unwrapObservable(e.bssid)},create:function(e){return new WiFiScanResultViewModel(e.data)}};t.results=ko.mapping.fromJS([],n),t.filteredResults=ko.mapping.fromJS([],n),t.fetching=ko.observable(!1),t.update=function(){var e=0<arguments.length&&void 0!==arguments[0]?arguments[0]:function(){};t.fetching(!0),$.get(s(),function(s){var e;0<s.length&&(s=s.sort(function(e,t){return e.ssid===t.ssid?e.rssi<t.rssi?1:-1:e.ssid<t.ssid?-1:1}),ko.mapping.fromJS(s,t.results),e=s.filter(function(t,e){return-80<=t.rssi&&e===s.findIndex(function(e){return t.ssid===e.ssid})}).sort(function(e,t){return e.rssi<t.rssi?1:-1}),ko.mapping.fromJS(e,t.filteredResults))},\"json\").always(function(){t.fetching(!1),e()})}}function LastValuesViewModel(){var a=this;a.remoteUrl=baseEndpoint+\"/lastvalues\",a.fetching=ko.observable(!1),a.lastValues=ko.observable(!1),a.values=ko.mapping.fromJS([]),a.entries=ko.mapping.fromJS([]);var r=\"\";a.update=function(e){void 0===e&&(e=function(){}),a.fetching(!0),$.get(a.remoteUrl,function(e){var t=[];if(\"\"!=e&&e!==r){r=e,a.entries.push({timestamp:(new Date).toISOString(),log:e});try{var s,n=JSON.parse(e);for(s in n){var o=n[s],i=\"\";s.startsWith(\"CT\")&&(i=\" W\"),s.startsWith(\"P\")&&(i=\" W\"),s.startsWith(\"E\")&&(i=\" Wh\"),s.startsWith(\"V\")&&(i=\" V\"),s.startsWith(\"T\")&&(i=\" \"+String.fromCharCode(176)+\"C\"),t.push({key:s,value:o+i})}a.lastValues(!0),ko.mapping.fromJS(t,a.values)}catch(e){console.error(e),a.lastValues(!1)}}else a.lastValues(\"\"!=e)},\"text\").always(function(){a.fetching(!1),e()})}}function PasswordViewModel(t){var e=this;e.show=ko.observable(!1),e.value=ko.computed({read:function(){return e.show()&&e.isDummy()?\"\":t()},write:function(e){t(e)}}),e.isDummy=ko.computed(function(){return[\"___DUMMY_PASSWORD___\",\"_DUMMY_PASSWORD\"].includes(t())})}function EmonEspViewModel(e,t,s){var n=this;n.baseHost=ko.observable(\"\"!==e?e:\"openevse.local\"),n.basePort=ko.observable(t),n.baseProtocol=ko.observable(s),n.baseEndpoint=ko.pureComputed(function(){var e=\"//\"+n.baseHost();return 80!==n.basePort()&&(e+=\":\"+n.basePort()),e}),n.wsEndpoint=ko.pureComputed(function(){var e=\"ws://\"+n.baseHost();return\"https:\"===n.baseProtocol()&&(e=\"wss://\"+n.baseHost()),80!==n.basePort()&&(e+=\":\"+n.basePort()),e+=\"/ws\"}),n.config=new ConfigViewModel,n.status=new StatusViewModel,n.last=new LastValuesViewModel,n.scan=new WiFiScanViewModel(n.baseEndpoint),n.wifi=new WiFiConfigViewModel(n.baseEndpoint,n.config,n.status,n.scan),n.wifiPassword=new PasswordViewModel(n.config.pass),n.emoncmsApiKey=new PasswordViewModel(n.config.emoncms_apikey),n.mqttPassword=new PasswordViewModel(n.config.mqtt_pass),n.wwwPassword=new PasswordViewModel(n.config.www_password),n.initialised=ko.observable(!1),n.updating=ko.observable(!1),n.wifi.selectedNet.subscribe(function(e){!1!==e&&n.config.ssid(e.ssid())}),n.config.ssid.subscribe(function(e){n.wifi.setSsid(e)});var o=null;n.upgradeUrl=ko.observable(\"about:blank\"),n.start=function(){n.updating(!0),n.config.update(function(){n.status.update(function(){n.last.update(function(){n.initialised(!0),o=setTimeout(n.update,1e3),n.upgradeUrl(baseEndpoint+\"/update\"),n.updating(!1)})})})},n.update=function(){n.updating()||(n.updating(!0),null!==o&&(clearTimeout(o),o=null),n.status.update(function(){n.last.update(function(){o=setTimeout(n.update,1e3),n.updating(!1)})}))},n.wifiConnecting=ko.observable(!1),n.status.mode.subscribe(function(e){\"STA+AP\"!==e&&\"STA\"!==e||n.wifiConnecting(!1)}),n.saveNetworkFetching=ko.observable(!1),n.saveNetworkSuccess=ko.observable(!1),n.saveNetwork=function(){\"\"===n.config.ssid()?alert(\"Please select network\"):(n.saveNetworkFetching(!0),n.saveNetworkSuccess(!1),$.post(baseEndpoint+\"/savenetwork\",{ssid:n.config.ssid(),pass:n.config.pass()},function(e){n.saveNetworkSuccess(!0),n.wifiConnecting(!0)}).fail(function(){alert(\"Failed to save WiFi config\")}).always(function(){n.saveNetworkFetching(!1)}))},n.saveAdminFetching=ko.observable(!1),n.saveAdminSuccess=ko.observable(!1),n.saveAdmin=function(){n.saveAdminFetching(!0),n.saveAdminSuccess(!1),$.post(baseEndpoint+\"/saveadmin\",{user:n.config.www_username(),pass:n.config.www_password()},function(e){n.saveAdminSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){n.saveAdminFetching(!1)})},n.saveTimerFetching=ko.observable(!1),n.saveTimerSuccess=ko.observable(!1),n.saveTimer=function(){n.saveTimerFetching(!0),n.saveTimerSuccess(!1),$.post(baseEndpoint+\"/savetimer\",{timer_start1:n.config.timer_start1(),timer_stop1:n.config.timer_stop1(),timer_start2:n.config.timer_start2(),timer_stop2:n.config.timer_stop2(),voltage_output:n.config.voltage_output(),time_offset:n.config.time_offset()},function(e){n.saveTimerSuccess(!0),setTimeout(function(){n.saveTimerSuccess(!1)},5e3)}).fail(function(){alert(\"Failed to save Timer config\")}).always(function(){n.saveTimerFetching(!1)})},n.ctrlMode=function(e){var t=n.status.ctrl_mode();n.status.ctrl_mode(e),$.post(baseEndpoint+\"/ctrlmode?mode=\"+e,{},function(e){}).fail(function(){n.status.ctrl_mode(t),alert(\"Failed to switch \"+e)})},n.saveEmonCmsFetching=ko.observable(!1),n.saveEmonCmsSuccess=ko.observable(!1),n.saveEmonCms=function(){var e={enable:n.config.emoncms_enabled(),server:n.config.emoncms_server(),path:n.config.emoncms_path(),apikey:n.config.emoncms_apikey(),node:n.config.emoncms_node(),fingerprint:n.config.emoncms_fingerprint()};\"\"===e.server||\"\"===e.node?alert(\"Please enter Emoncms server and node\"):32==e.apikey.length||n.emoncmsApiKey.isDummy()?\"\"!==e.fingerprint&&59!=e.fingerprint.length?alert(\"Please enter valid SSL SHA-1 fingerprint\"):(n.saveEmonCmsFetching(!0),n.saveEmonCmsSuccess(!1),$.post(baseEndpoint+\"/saveemoncms\",e,function(e){n.saveEmonCmsSuccess(!0)}).fail(function(){alert(\"Failed to save Admin config\")}).always(function(){n.saveEmonCmsFetching(!1)})):alert(\"Please enter valid Emoncms apikey\")},n.saveMqttFetching=ko.observable(!1),n.saveMqttSuccess=ko.observable(!1),n.saveMqtt=function(){var e={enable:n.config.mqtt_enabled(),server:n.config.mqtt_server(),port:n.config.mqtt_port(),topic:n.config.mqtt_topic(),prefix:n.config.mqtt_feed_prefix(),user:n.config.mqtt_user(),pass:n.config.mqtt_pass()};\"\"===e.server?alert(\"Please enter MQTT server\"):(n.saveMqttFetching(!0),n.saveMqttSuccess(!1),$.post(baseEndpoint+\"/savemqtt\",e,function(e){n.saveMqttSuccess(!0)}).fail(function(){alert(\"Failed to save MQTT config\")}).always(function(){n.saveMqttFetching(!1)}))}}BaseViewModel.prototype.update=function(e){void 0===e&&(e=function(){});var t=this;t.fetching(!0),$.get(t.remoteUrl,function(e){ko.mapping.fromJS(e,t)},\"json\").always(function(){t.fetching(!1),e()})},StatusViewModel.prototype=Object.create(BaseViewModel.prototype),StatusViewModel.prototype.constructor=StatusViewModel,ConfigViewModel.prototype=Object.create(BaseViewModel.prototype),ConfigViewModel.prototype.constructor=ConfigViewModel,self.updateFetching=ko.observable(!1),self.updateComplete=ko.observable(!1),self.updateError=ko.observable(\"\"),self.updateFilename=ko.observable(\"\"),self.updateLoaded=ko.observable(0),self.updateTotal=ko.observable(1),self.updateProgress=ko.pureComputed(function(){return self.updateLoaded()/self.updateTotal()*100}),self.otaUpdate=function(){var e;\"\"!==self.updateFilename()?(self.updateFetching(!0),self.updateError(\"\"),e=$(\"#upload_form\")[0],e=new FormData(e),$.ajax({url:\"/upload\",type:\"POST\",data:e,contentType:!1,processData:!1,xhr:function(){var e;return(e=new window.XMLHttpRequest).upload.addEventListener(\"progress\",function(e){e.lengthComputable&&(self.updateLoaded(e.loaded),self.updateTotal(e.total))},!1),e}}).done(function(e){console.log(e),\"OK\"==e?(self.updateComplete(!0),setTimeout(function(){location.reload()},5e3)):self.updateError(e)}).fail(function(){self.updateError(\"HTTP Update failed\")}).always(function(){self.updateFetching(!1)})):self.updateError(\"Filename not set\")};var development=\"\",baseHost=window.location.hostname,basePort=window.location.port,baseProtocol=window.location.protocol,baseEndpoint=\"//\"+baseHost;80!==basePort&&(baseEndpoint+=\":\"+basePort),baseEndpoint+=development;var statusupdate=!1,selected_network_ssid=\"\",lastmode=\"\",ipaddress=\"\";function scaleString(e,t,s){return(parseInt(e)/t).toFixed(s)}function addcolon(e){return(e=new String(e)).length<3?\"00:00\":(e=3==e.length?\"0\"+e:e).substr(0,2)+\":\"+e.substr(2,4)}function toggle(e){e=document.getElementById(e);\"block\"==e.style.display?e.style.display=\"none\":e.style.display=\"block\"}$(function(){var e=new EmonEspViewModel(baseHost,basePort,baseProtocol);ko.applyBindings(e),e.start()}),document.getElementById(\"apoff\").addEventListener(\"click\",function(e){var t=new XMLHttpRequest;t.open(\"POST\",\"apoff\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),document.getElementById(\"apoff\").style.display=\"none\",\"\"!==ipaddress&&(window.location=\"http://\"+ipaddress))},t.send()}),document.getElementById(\"reset\").addEventListener(\"click\",function(e){var t;confirm(\"CAUTION: Do you really want to Factory Reset? All setting and config will be lost.\")&&((t=new XMLHttpRequest).open(\"POST\",\"reset\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),0!==e&&(document.getElementById(\"reset\").innerHTML=\"Resetting...\"))},t.send())}),document.getElementById(\"restart\").addEventListener(\"click\",function(e){var t;confirm(\"Restart emonESP? Current config will be saved, takes approximately 10s.\")&&((t=new XMLHttpRequest).open(\"POST\",\"restart\",!0),t.onreadystatechange=function(){var e;4==t.readyState&&200==t.status&&(e=t.responseText,console.log(e),0!==e&&(document.getElementById(\"reset\").innerHTML=\"Restarting\"))},t.send())});\n"
  "//# sourceMappingURL=config.js.map\n";
