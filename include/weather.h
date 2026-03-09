// Helpers used by the display lambda.
#include <cmath>
#include <cctype>
#include <string>

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

const char* getAllergyRatingShort(const std::string rating) {
  // IQVIA ratings per HA docs:
  // Low, Low/Medium, Medium, Medium/High, High.
  // Keep this short so it doesn't overlap adjacent fields.
  if (rating == "Low") return "Low";
  if (rating == "Low/Medium") return "MedLow";
  if (rating == "Medium") return "Med";
  if (rating == "Medium/High") return "MedHigh";
  if (rating == "High") return "High";

  // Generic fallback: for "Foo/Bar" return "F/B"
  auto slash = rating.find('/');
  if (slash != std::string::npos && slash > 0 && slash + 1 < rating.size()) {
    static char out[4];
    out[0] = rating[0];
    out[1] = '/';
    out[2] = rating[slash + 1];
    out[3] = 0;
    return out;
  }

  // As a last resort, return empty string (prints just the numeric value).
  return "";
}

const char* getPollutionLevelShort(const std::string level) {
  // AirVisual (IQAir) enum values in HA:
  // good, moderate, unhealthy_sensitive, unhealthy, very_unhealthy, hazardous
  if (level == "good") return "Good";
  if (level == "moderate") return "Moderate";
  if (level == "unhealthy_sensitive") return "Unhealthy";
  if (level == "unhealthy") return "Unhealthy";
  if (level == "very_unhealthy") return "Unhealthy";
  if (level == "hazardous") return "Hazard";

  // Fallback: capitalize first letter, keep it short.
  static char out[8];
  size_t n = level.size();
  if (n == 0) return "";
  out[0] = (char) toupper(level[0]);
  size_t i = 1;
  for (; i < sizeof(out) - 1 && i < n; i++) {
    char c = level[i];
    if (c == '_') c = '-';
    out[i] = c;
  }
  out[i] = 0;
  return out;
}