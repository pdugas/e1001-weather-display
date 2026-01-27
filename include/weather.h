const char* getConditionIcon(const std::string condition) {
  if (condition == "sunny") {
    return "\U000F0599";
  } else if (condition == "partlycloudy") {
    return "\U000F0595";
  } else if (condition == "cloudy") {
    return "\U000F0590";
  } else if (condition == "rainy") {
    return "\U000F0597";
  } else if (condition == "snowy") {
    return "\U000F0598";
  } else if (condition == "pouring") {
    return "\U000F0596";      
  } else if (condition == "lightning") {
    return "\U000F0593";      
  } else if (condition == "clear-night") {
    return "\U000F0594";  
  } else if (condition == "night-partlycloudy") {
    return "\U000F0F31";    
  } else if (condition == "fog") {
    return "\U000F0591";    
  } else if (condition == "hail") {
    return "\U000F0592";  
  } else if (condition == "lightning-rainy") {
    return "\U000F067E";           
  } else if (condition == "snowy-rainy") {
    return "\U000F0F35";           
  } else if (condition == "windy") {
    return "\U000F059D";     
  } else if (condition == "windy-variant") {
    return "\U000F059E";                         
  } else if (condition == "exceptional") {
    return "\U000F0F2F";     
  } else {        
    return "\U000F0F2F"; 
  }
}