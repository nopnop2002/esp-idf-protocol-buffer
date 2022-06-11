/* The example of ESP-IDF
 *
 * This sample code is in the public domain.
 */

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "amessage.pb-c.h"

#define TAG "MAIN"

void app_main()
{
	AMessage msg = AMESSAGE__INIT; // AMessage
	void *buf;                     // Buffer to store serialized data
	unsigned len;                  // Length of serialized data

	msg.a = 10;
	msg.has_b = 1;
	msg.b = 2;
	len = amessage__get_packed_size(&msg);
	buf = malloc(len);
	amessage__pack(&msg,buf);
	ESP_LOGI(TAG, "Writing %d serialized bytes",len); // See the length of message
	ESP_LOG_BUFFER_HEXDUMP(TAG, buf, len, ESP_LOG_INFO); // Write to stdout to allow direct command line piping


	// Unpack the message using protobuf-c.
	AMessage *msg2;
	msg2 = amessage__unpack(NULL, len, buf);
	if (msg2 == NULL) {
    	ESP_LOGE(TAG, "error unpacking incoming message");
	}

	// display the message's fields.
	ESP_LOGI(TAG, "deserialize: a=%d",msg2->a);  // required field
 	if (msg2->has_b) // handle optional field
    	ESP_LOGI(TAG, "deserialize: b=%d",msg2->b);

	// Free the allocated serialized buffer
	free(buf);

	// Free the allocated deserialized buffer
	amessage__free_unpacked(msg2, NULL);

}
