<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Primary function overlay winकरोw definitions
 * and service functions used by LPDDR chips
 */
#अगर_अघोषित __LINUX_MTD_PFOW_H
#घोषणा __LINUX_MTD_PFOW_H

#समावेश <linux/mtd/qinfo.h>

/* PFOW रेजिस्टरs addressing */
/* Address of symbol "P" */
#घोषणा PFOW_QUERY_STRING_P			0x0000
/* Address of symbol "F" */
#घोषणा PFOW_QUERY_STRING_F			0x0002
/* Address of symbol "O" */
#घोषणा PFOW_QUERY_STRING_O			0x0004
/* Address of symbol "W" */
#घोषणा PFOW_QUERY_STRING_W			0x0006
/* Identअगरication info क्रम LPDDR chip */
#घोषणा PFOW_MANUFACTURER_ID			0x0020
#घोषणा PFOW_DEVICE_ID				0x0022
/* Address in PFOW where prog buffer can be found */
#घोषणा PFOW_PROGRAM_BUFFER_OFFSET		0x0040
/* Size of program buffer in words */
#घोषणा PFOW_PROGRAM_BUFFER_SIZE		0x0042
/* Address command code रेजिस्टर */
#घोषणा PFOW_COMMAND_CODE			0x0080
/* command data रेजिस्टर */
#घोषणा PFOW_COMMAND_DATA			0x0084
/* command address रेजिस्टर lower address bits */
#घोषणा PFOW_COMMAND_ADDRESS_L			0x0088
/* command address रेजिस्टर upper address bits */
#घोषणा PFOW_COMMAND_ADDRESS_H			0x008a
/* number of bytes to be proggrammed lower address bits */
#घोषणा PFOW_DATA_COUNT_L			0x0090
/* number of bytes to be proggrammed higher address bits */
#घोषणा PFOW_DATA_COUNT_H			0x0092
/* command execution रेजिस्टर, the only possible value is 0x01 */
#घोषणा PFOW_COMMAND_EXECUTE			0x00c0
/* 0x01 should be written at this address to clear buffer */
#घोषणा PFOW_CLEAR_PROGRAM_BUFFER		0x00c4
/* device program/erase suspend रेजिस्टर */
#घोषणा PFOW_PROGRAM_ERASE_SUSPEND		0x00c8
/* device status रेजिस्टर */
#घोषणा PFOW_DSR				0x00cc

/* LPDDR memory device command codes */
/* They are possible values of PFOW command code रेजिस्टर */
#घोषणा LPDDR_WORD_PROGRAM		0x0041
#घोषणा LPDDR_BUFF_PROGRAM		0x00E9
#घोषणा LPDDR_BLOCK_ERASE		0x0020
#घोषणा LPDDR_LOCK_BLOCK		0x0061
#घोषणा LPDDR_UNLOCK_BLOCK		0x0062
#घोषणा LPDDR_READ_BLOCK_LOCK_STATUS	0x0065
#घोषणा LPDDR_INFO_QUERY		0x0098
#घोषणा LPDDR_READ_OTP			0x0097
#घोषणा LPDDR_PROG_OTP			0x00C0
#घोषणा LPDDR_RESUME			0x00D0

/* Defines possible value of PFOW command execution रेजिस्टर */
#घोषणा LPDDR_START_EXECUTION			0x0001

/* Defines possible value of PFOW program/erase suspend रेजिस्टर */
#घोषणा LPDDR_SUSPEND				0x0001

/* Possible values of PFOW device status रेजिस्टर */
/* access R - पढ़ो; RC पढ़ो & clearable */
#घोषणा DSR_DPS			(1<<1) /* RC; device protect status
					* 0 - not रक्षित 1 - locked */
#घोषणा DSR_PSS			(1<<2) /* R; program suspend status;
					* 0-prog in progress/completed,
					* 1- prog suspended */
#घोषणा DSR_VPPS		(1<<3) /* RC; 0-Vpp OK, * 1-Vpp low */
#घोषणा DSR_PROGRAM_STATUS	(1<<4) /* RC; 0-successful, 1-error */
#घोषणा DSR_ERASE_STATUS	(1<<5) /* RC; erase or blank check status;
					* 0-success erase/blank check,
					* 1 blank check error */
#घोषणा DSR_ESS			(1<<6) /* R; erase suspend status;
					* 0-erase in progress/complete,
					* 1 erase suspended */
#घोषणा DSR_READY_STATUS	(1<<7) /* R; Device status
					* 0-busy,
					* 1-पढ़ोy */
#घोषणा DSR_RPS			(0x3<<8) /* RC;  region program status
					* 00 - Success,
					* 01-re-program attempt in region with
					* object mode data,
					* 10-object mode program w attempt in
					* region with control mode data
					* 11-attempt to program invalid half
					* with 0x41 command */
#घोषणा DSR_AOS			(1<<12) /* RC; 1- AO related failure */
#घोषणा DSR_AVAILABLE		(1<<15) /* R; Device availbility
					* 1 - Device available
					* 0 - not available */

/* The superset of all possible error bits in DSR */
#घोषणा DSR_ERR			0x133A

अटल अंतरभूत व्योम send_pfow_command(काष्ठा map_info *map,
				अचिन्हित दीर्घ cmd_code, अचिन्हित दीर्घ adr,
				अचिन्हित दीर्घ len, map_word *datum)
अणु
	पूर्णांक bits_per_chip = map_bankwidth(map) * 8;

	map_ग_लिखो(map, CMD(cmd_code), map->pfow_base + PFOW_COMMAND_CODE);
	map_ग_लिखो(map, CMD(adr & ((1<<bits_per_chip) - 1)),
				map->pfow_base + PFOW_COMMAND_ADDRESS_L);
	map_ग_लिखो(map, CMD(adr>>bits_per_chip),
				map->pfow_base + PFOW_COMMAND_ADDRESS_H);
	अगर (len) अणु
		map_ग_लिखो(map, CMD(len & ((1<<bits_per_chip) - 1)),
					map->pfow_base + PFOW_DATA_COUNT_L);
		map_ग_लिखो(map, CMD(len>>bits_per_chip),
					map->pfow_base + PFOW_DATA_COUNT_H);
	पूर्ण
	अगर (datum)
		map_ग_लिखो(map, *datum, map->pfow_base + PFOW_COMMAND_DATA);

	/* Command execution start */
	map_ग_लिखो(map, CMD(LPDDR_START_EXECUTION),
			map->pfow_base + PFOW_COMMAND_EXECUTE);
पूर्ण
#पूर्ण_अगर /* __LINUX_MTD_PFOW_H */
