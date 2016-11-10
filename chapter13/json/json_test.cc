#include <iostream>
#include <json/json.h>

using namespace std;

int main(){
  //create json object json_temp
  Json::Value json_temp;
  json_temp["name"] = Json::Value("zhouyang");
  json_temp["age"] = Json::Value(22);

  //create json object root
  Json::Value root;
  root["key_string"] = Json::Value("value string");
  root["key_number"] = Json::Value(12345);
  root["key_boolean"] = Json::Value(false);
  root["key_double"] = Json::Value(11.11);
  //将json_temp加入root中去
  root["key_object"] = json_temp;
  root["key_array"].append("array_string");
  root["key_array"].append(1234);

  Json::FastWriter fast_writer;
  cout<<fast_writer.write(root);
  cout<<endl;

  Json::StyledWriter styled_writer;
  cout<<styled_writer.write(root);
  cout<<endl;

  string json_str = "{\"id\":1, \"name\":\"zhouyang\"}";
  Json::Reader reader;
  Json::Value value;
  //parse json string
  if(!reader.parse(json_str,value)){
    cout<<"parse error!"<<endl;
    return 0;
  }

  string name = value["name"].asString();
  cout<<name<<endl;

  cout<<value["name"]<<endl;
  cout<<endl;

  //if id is int ?
  if(!value["id"].isInt()){
    cout<<"id is not int!"<<endl;
  }
  else{
    int id = value["id"].asInt();
    cout<<"id = "<<id<<endl;
  }
  return 0;

}