<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVBIOS_I2C_H__
#घोषणा __NVBIOS_I2C_H__
क्रमागत dcb_i2c_type अणु
	/* matches bios type field prior to ccb 4.1 */
	DCB_I2C_NV04_BIT = 0x00,
	DCB_I2C_NV4E_BIT = 0x04,
	DCB_I2C_NVIO_BIT = 0x05,
	DCB_I2C_NVIO_AUX = 0x06,
	/* made up - mostly */
	DCB_I2C_PMGR     = 0x80,
	DCB_I2C_UNUSED   = 0xff
पूर्ण;

काष्ठा dcb_i2c_entry अणु
	क्रमागत dcb_i2c_type type;
	u8 drive;
	u8 sense;
	u8 share;
	u8 auxch;
पूर्ण;

u16 dcb_i2c_table(काष्ठा nvkm_bios *, u8 *ver, u8 *hdr, u8 *cnt, u8 *len);
u16 dcb_i2c_entry(काष्ठा nvkm_bios *, u8 index, u8 *ver, u8 *len);
पूर्णांक dcb_i2c_parse(काष्ठा nvkm_bios *, u8 index, काष्ठा dcb_i2c_entry *);
#पूर्ण_अगर
