#include <iostream>
#include <string>
#include <boost/asio/deadline_timer.hpp>
#include "cJSON.h"

using std::cout; using std::cerr; using std::endl;

char* create_monitor();
char* create_monitor2();
int supports_full_hd(const char * const monitor);

const char *ajson = R"({"name":"Awesome 4K","resolutions":[{"width":1280,"height":720},{"width":1920,"height":1080},{"width":3840,"height":2160}]})";

int main() {
	
	//cout << create_monitor() << endl << endl << create_monitor2();

	//cout << (supports_full_hd(ajson) ? "true" : "false") << endl;

	const std::string strb(200, '\r');
	const std::string strk(200, ' ');
	const std::string stro(200, 'o');
	const std::string strq(200, 'q');
	
	cout << stro << stro;
	boost::asio::io_context io;
	boost::asio::deadline_timer(io, boost::posix_time::seconds(2)).wait();
	cout  << strb << strq;

	system("pause");

	return 0;
}

//create a monitor with a list of supported resolutions
char* create_monitor(void){
	cJSON *monitor = nullptr;

	try {
		const unsigned int resolution_numbers[3][2] = {
			{ 1280, 720 },
			{ 1920, 1080 },
			{ 3840, 2160 }
		};
		
		size_t index = 0;

		monitor = cJSON_CreateObject();
		if (monitor == nullptr) throw;

		cJSON *name = cJSON_CreateString("Awesome 4K");
		if (name == nullptr) throw;

		/* after creation was successful, immediately add it to the monitor,
		* thereby transfering ownership of the pointer to it */
		cJSON_AddItemToObject(monitor, "name", name);

		cJSON *resolutions = cJSON_CreateArray();
		if (resolutions == nullptr) throw;

		cJSON_AddItemToObject(monitor, "resolutions", resolutions);

		for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index) {

			cJSON *resolution = cJSON_CreateObject(); 
			if (resolution == nullptr) throw;

			cJSON_AddItemToArray(resolutions, resolution);

			cJSON *width = cJSON_CreateNumber(resolution_numbers[index][0]);
			if (width == nullptr) throw;

			cJSON_AddItemToObject(resolution, "width", width);

			cJSON *height = cJSON_CreateNumber(resolution_numbers[index][1]);
			if (height == nullptr) throw;

			cJSON_AddItemToObject(resolution, "height", height);
		}

		char *string = cJSON_Print(monitor);
		if (string == nullptr) cerr << "Failed to print monitor.\n";

		cJSON_Delete(monitor);
		return string;
	} catch(...){
		cerr << "Error occurs!" << endl;
		cJSON_Delete(monitor);
		return nullptr;
	}
}

char* create_monitor2(void) {  // by self
	
	decltype(cJSON_CreateObject()) monitor = nullptr;
	decltype(cJSON_Print(monitor)) fin_string = nullptr;
	try {
		if(!(monitor = cJSON_CreateObject())) throw;
		if(!cJSON_AddStringToObject(monitor, "name", "Awesome 4K")) throw;
		auto *resolution_arr = cJSON_AddArrayToObject(monitor, "resolutions"); if (!resolution_arr) throw;
		auto resolution_items = { cJSON_CreateObject(), cJSON_CreateObject(), cJSON_CreateObject() };

		for (auto &item : resolution_items) {
			if (!item) throw;
			cJSON_AddNumberToObject(item, "width", 1280);
			cJSON_AddNumberToObject(item, "height", 720);
			cJSON_AddItemToArray(resolution_arr, item);
		}
		if(!(fin_string = cJSON_PrintUnformatted(monitor))) throw;

	}catch(...) {
		cerr << "Error occurs!" << endl;
	}
	cJSON_Delete(monitor);

	return fin_string;
}

int supports_full_hd(const char * const monitor)
{
	const cJSON *resolution = NULL;
	const cJSON *resolutions = NULL;
	const cJSON *name = NULL;
	int status = 0;
	cJSON *monitor_json = cJSON_Parse(monitor);

	if (monitor_json == NULL){

		const char *error_ptr = cJSON_GetErrorPtr();
		if (error_ptr != NULL){
			fprintf(stderr, "Error before: %s\n", error_ptr);
		}
		status = 0;
		goto end;
	}

	name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
	
	if (cJSON_IsString(name) && (name->valuestring != NULL)){
		printf("Checking monitor \"%s\"\n", name->valuestring);
	}

	resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
	
	cJSON_ArrayForEach(resolution, resolutions){

		cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
		cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");

		if (!(cJSON_IsNumber(width) && cJSON_IsNumber(height)) || status){
			status = 0;
			goto end;
		}
		cout << "isObject:" << (cJSON_IsObject(resolution) ? "true" : "false") << "  width:" << width->valuedouble << "  height:" << height->valuedouble << endl;
	}

end:
	cJSON_Delete(monitor_json);
	return status;
}

