<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
काष्ठा acpi_smb_hc;
क्रमागत acpi_smb_protocol अणु
	SMBUS_WRITE_QUICK = 2,
	SMBUS_READ_QUICK = 3,
	SMBUS_SEND_BYTE = 4,
	SMBUS_RECEIVE_BYTE = 5,
	SMBUS_WRITE_BYTE = 6,
	SMBUS_READ_BYTE = 7,
	SMBUS_WRITE_WORD  = 8,
	SMBUS_READ_WORD  = 9,
	SMBUS_WRITE_BLOCK = 0xa,
	SMBUS_READ_BLOCK = 0xb,
	SMBUS_PROCESS_CALL = 0xc,
	SMBUS_BLOCK_PROCESS_CALL = 0xd,
पूर्ण;

क्रमागत acpi_sbs_device_addr अणु
	ACPI_SBS_CHARGER = 0x9,
	ACPI_SBS_MANAGER = 0xa,
	ACPI_SBS_BATTERY = 0xb,
पूर्ण;

प्रकार व्योम (*smbus_alarm_callback)(व्योम *context);

बाह्य पूर्णांक acpi_smbus_पढ़ो(काष्ठा acpi_smb_hc *hc, u8 protocol, u8 address,
		u8 command, u8 *data);
बाह्य पूर्णांक acpi_smbus_ग_लिखो(काष्ठा acpi_smb_hc *hc, u8 protocol, u8 slave_address,
		u8 command, u8 *data, u8 length);
बाह्य पूर्णांक acpi_smbus_रेजिस्टर_callback(काष्ठा acpi_smb_hc *hc,
		smbus_alarm_callback callback, व्योम *context);
बाह्य पूर्णांक acpi_smbus_unरेजिस्टर_callback(काष्ठा acpi_smb_hc *hc);
