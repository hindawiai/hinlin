<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_MTD_QINFO_H
#घोषणा __LINUX_MTD_QINFO_H

#समावेश <linux/mtd/map.h>
#समावेश <linux/रुको.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/mtd/partitions.h>

/* lpddr_निजी describes lpddr flash chip in memory map
 * @ManufactId - Chip Manufacture ID
 * @DevId - Chip Device ID
 * @qinfo - poपूर्णांकer to qinfo records describing the chip
 * @numchips - number of chips including virual RWW partitions
 * @chipshअगरt - Chip/partition size 2^chipshअगरt
 * @chips - per-chip data काष्ठाure
 */
काष्ठा lpddr_निजी अणु
	uपूर्णांक16_t ManufactId;
	uपूर्णांक16_t DevId;
	काष्ठा qinfo_chip *qinfo;
	पूर्णांक numchips;
	अचिन्हित दीर्घ chipshअगरt;
	काष्ठा flchip chips[];
पूर्ण;

/* qinfo_query_info काष्ठाure contains request inक्रमmation क्रम
 * each qinfo record
 * @major - major number of qinfo record
 * @major - minor number of qinfo record
 * @id_str - descriptive string to access the record
 * @desc - detailed description क्रम the qinfo record
 */
काष्ठा qinfo_query_info अणु
	uपूर्णांक8_t	major;
	uपूर्णांक8_t	minor;
	अक्षर *id_str;
	अक्षर *desc;
पूर्ण;

/*
 * qinfo_chip काष्ठाure contains necessary qinfo records data
 * @DevSizeShअगरt - Device size 2^n bytes
 * @BufSizeShअगरt - Program buffer size 2^n bytes
 * @TotalBlocksNum - Total number of blocks
 * @UnअगरormBlockSizeShअगरt - Unअगरorm block size 2^UnअगरormBlockSizeShअगरt bytes
 * @HWPartsNum - Number of hardware partitions
 * @SuspEraseSupp - Suspend erase supported
 * @SingleWordProgTime - Single word program 2^SingleWordProgTime u-sec
 * @ProgBufferTime - Program buffer ग_लिखो 2^ProgBufferTime u-sec
 * @BlockEraseTime - Block erase 2^BlockEraseTime m-sec
 */
काष्ठा qinfo_chip अणु
	/* General device info */
	uपूर्णांक16_t DevSizeShअगरt;
	uपूर्णांक16_t BufSizeShअगरt;
	/* Erase block inक्रमmation */
	uपूर्णांक16_t TotalBlocksNum;
	uपूर्णांक16_t UnअगरormBlockSizeShअगरt;
	/* Partition inक्रमmation */
	uपूर्णांक16_t HWPartsNum;
	/* Optional features */
	uपूर्णांक16_t SuspEraseSupp;
	/* Operation typical समय */
	uपूर्णांक16_t SingleWordProgTime;
	uपूर्णांक16_t ProgBufferTime;
	uपूर्णांक16_t BlockEraseTime;
पूर्ण;

/* defines क्रम fixup usage */
#घोषणा LPDDR_MFR_ANY		0xffff
#घोषणा LPDDR_ID_ANY		0xffff
#घोषणा NUMONYX_MFGR_ID		0x0089
#घोषणा R18_DEVICE_ID_1G	0x893c

अटल अंतरभूत map_word lpddr_build_cmd(u_दीर्घ cmd, काष्ठा map_info *map)
अणु
	map_word val = अणु अणु0पूर्ण पूर्ण;
	val.x[0] = cmd;
	वापस val;
पूर्ण

#घोषणा CMD(x) lpddr_build_cmd(x, map)
#घोषणा CMDVAL(cmd) cmd.x[0]

काष्ठा mtd_info *lpddr_cmdset(काष्ठा map_info *);

#पूर्ण_अगर

