<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Subdriver क्रम the GL860 chip with the OV2640 sensor
 * Author Olivier LORIN, from Malmostoso's logs
 */

/* Sensor : OV2640 */

#समावेश "gl860.h"

अटल u8 dat_init1[] = "\x00\x41\x07\x6a\x06\x61\x0d\x6a" "\x10\x10\xc1\x01";

अटल u8 c61[] = अणु0x61पूर्ण; /* expected */
अटल u8 c51[] = अणु0x51पूर्ण; /* expected */
अटल u8 c50[] = अणु0x50पूर्ण; /* expected */
अटल u8 c28[] = अणु0x28पूर्ण; /* expected */
अटल u8 ca8[] = अणु0xa8पूर्ण; /* expected */

अटल u8 dat_post[] =
	"\x00\x41\x07\x6a\x06\xef\x0d\x6a" "\x10\x10\xc1\x01";

अटल u8 dat_640[]  = "\xd0\x01\xd1\x08\xd2\xe0\xd3\x02\xd4\x10\xd5\x81";
अटल u8 dat_800[]  = "\xd0\x01\xd1\x10\xd2\x58\xd3\x02\xd4\x18\xd5\x21";
अटल u8 dat_1280[] = "\xd0\x01\xd1\x18\xd2\xc0\xd3\x02\xd4\x28\xd5\x01";
अटल u8 dat_1600[] = "\xd0\x01\xd1\x20\xd2\xb0\xd3\x02\xd4\x30\xd5\x41";

अटल काष्ठा validx tbl_init_at_startup[] = अणु
	अणु0x0000, 0x0000पूर्ण, अणु0x0010, 0x0010पूर्ण, अणु0x0008, 0x00c0पूर्ण, अणु0x0001, 0x00c1पूर्ण,
	अणु0x0001, 0x00c2पूर्ण, अणु0x0020, 0x0006पूर्ण, अणु0x006a, 0x000dपूर्ण,
	अणु0x0050, 0x0000पूर्ण, अणु0x0041, 0x0000पूर्ण, अणु0x006a, 0x0007पूर्ण, अणु0x0061, 0x0006पूर्ण,
	अणु0x006a, 0x000dपूर्ण, अणु0x0000, 0x00c0पूर्ण, अणु0x0010, 0x0010पूर्ण, अणु0x0001, 0x00c1पूर्ण,
	अणु0x0041, 0x00c2पूर्ण, अणु0x0004, 0x00d8पूर्ण, अणु0x0012, 0x0004पूर्ण, अणु0x0000, 0x0058पूर्ण,
	अणु0x0041, 0x0000पूर्ण, अणु0x0061, 0x0000पूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_common[] = अणु
	अणु0x6000, 0x00ffपूर्ण, अणु0x60ff, 0x002cपूर्ण, अणु0x60df, 0x002eपूर्ण, अणु0x6001, 0x00ffपूर्ण,
	अणु0x6080, 0x0012पूर्ण, अणु0x6000, 0x0000पूर्ण, अणु0x6000, 0x0045पूर्ण, अणु0x6000, 0x0010पूर्ण,
	अणु0x6035, 0x003cपूर्ण, अणु0x6000, 0x0011पूर्ण, अणु0x6028, 0x0004पूर्ण, अणु0x60e5, 0x0013पूर्ण,
	अणु0x6088, 0x0014पूर्ण, अणु0x600c, 0x002cपूर्ण, अणु0x6078, 0x0033पूर्ण, अणु0x60f7, 0x003bपूर्ण,
	अणु0x6000, 0x003eपूर्ण, अणु0x6011, 0x0043पूर्ण, अणु0x6010, 0x0016पूर्ण, अणु0x6082, 0x0039पूर्ण,
	अणु0x6088, 0x0035पूर्ण, अणु0x600a, 0x0022पूर्ण, अणु0x6040, 0x0037पूर्ण, अणु0x6000, 0x0023पूर्ण,
	अणु0x60a0, 0x0034पूर्ण, अणु0x601a, 0x0036पूर्ण, अणु0x6002, 0x0006पूर्ण, अणु0x60c0, 0x0007पूर्ण,
	अणु0x60b7, 0x000dपूर्ण, अणु0x6001, 0x000eपूर्ण, अणु0x6000, 0x004cपूर्ण, अणु0x6081, 0x004aपूर्ण,
	अणु0x6099, 0x0021पूर्ण, अणु0x6002, 0x0009पूर्ण, अणु0x603e, 0x0024पूर्ण, अणु0x6034, 0x0025पूर्ण,
	अणु0x6081, 0x0026पूर्ण, अणु0x6000, 0x0000पूर्ण, अणु0x6000, 0x0045पूर्ण, अणु0x6000, 0x0010पूर्ण,
	अणु0x6000, 0x005cपूर्ण, अणु0x6000, 0x0063पूर्ण, अणु0x6000, 0x007cपूर्ण, अणु0x6070, 0x0061पूर्ण,
	अणु0x6080, 0x0062पूर्ण, अणु0x6080, 0x0020पूर्ण, अणु0x6030, 0x0028पूर्ण, अणु0x6000, 0x006cपूर्ण,
	अणु0x6000, 0x006eपूर्ण, अणु0x6002, 0x0070पूर्ण, अणु0x6094, 0x0071पूर्ण, अणु0x60c1, 0x0073पूर्ण,
	अणु0x6034, 0x003dपूर्ण, अणु0x6057, 0x005aपूर्ण, अणु0x60bb, 0x004fपूर्ण, अणु0x609c, 0x0050पूर्ण,
	अणु0x6080, 0x006dपूर्ण, अणु0x6002, 0x0039पूर्ण, अणु0x6033, 0x003aपूर्ण, अणु0x60f1, 0x003bपूर्ण,
	अणु0x6031, 0x003cपूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x6014, 0x00e0पूर्ण, अणु0x60ff, 0x0076पूर्ण,
	अणु0x60a0, 0x0033पूर्ण, अणु0x6020, 0x0042पूर्ण, अणु0x6018, 0x0043पूर्ण, अणु0x6000, 0x004cपूर्ण,
	अणु0x60d0, 0x0087पूर्ण, अणु0x600f, 0x0088पूर्ण, अणु0x6003, 0x00d7पूर्ण, अणु0x6010, 0x00d9पूर्ण,
	अणु0x6005, 0x00daपूर्ण, अणु0x6082, 0x00d3पूर्ण, अणु0x60c0, 0x00f9पूर्ण, अणु0x6006, 0x0044पूर्ण,
	अणु0x6007, 0x00d1पूर्ण, अणु0x6002, 0x00d2पूर्ण, अणु0x6000, 0x00d2पूर्ण, अणु0x6011, 0x00d8पूर्ण,
	अणु0x6008, 0x00c8पूर्ण, अणु0x6080, 0x00c9पूर्ण, अणु0x6008, 0x007cपूर्ण, अणु0x6020, 0x007dपूर्ण,
	अणु0x6020, 0x007dपूर्ण, अणु0x6000, 0x0090पूर्ण, अणु0x600e, 0x0091पूर्ण, अणु0x601a, 0x0091पूर्ण,
	अणु0x6031, 0x0091पूर्ण, अणु0x605a, 0x0091पूर्ण, अणु0x6069, 0x0091पूर्ण, अणु0x6075, 0x0091पूर्ण,
	अणु0x607e, 0x0091पूर्ण, अणु0x6088, 0x0091पूर्ण, अणु0x608f, 0x0091पूर्ण, अणु0x6096, 0x0091पूर्ण,
	अणु0x60a3, 0x0091पूर्ण, अणु0x60af, 0x0091पूर्ण, अणु0x60c4, 0x0091पूर्ण, अणु0x60d7, 0x0091पूर्ण,
	अणु0x60e8, 0x0091पूर्ण, अणु0x6020, 0x0091पूर्ण, अणु0x6000, 0x0092पूर्ण, अणु0x6006, 0x0093पूर्ण,
	अणु0x60e3, 0x0093पूर्ण, अणु0x6005, 0x0093पूर्ण, अणु0x6005, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण,
	अणु0x6004, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण,
	अणु0x6000, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण, अणु0x6000, 0x0093पूर्ण,
	अणु0x6000, 0x0096पूर्ण, अणु0x6008, 0x0097पूर्ण, अणु0x6019, 0x0097पूर्ण, अणु0x6002, 0x0097पूर्ण,
	अणु0x600c, 0x0097पूर्ण, अणु0x6024, 0x0097पूर्ण, अणु0x6030, 0x0097पूर्ण, अणु0x6028, 0x0097पूर्ण,
	अणु0x6026, 0x0097पूर्ण, अणु0x6002, 0x0097पूर्ण, अणु0x6098, 0x0097पूर्ण, अणु0x6080, 0x0097पूर्ण,
	अणु0x6000, 0x0097पूर्ण, अणु0x6000, 0x0097पूर्ण, अणु0x60ed, 0x00c3पूर्ण, अणु0x609a, 0x00c4पूर्ण,
	अणु0x6000, 0x00a4पूर्ण, अणु0x6011, 0x00c5पूर्ण, अणु0x6051, 0x00c6पूर्ण, अणु0x6010, 0x00c7पूर्ण,
	अणु0x6066, 0x00b6पूर्ण, अणु0x60a5, 0x00b8पूर्ण, अणु0x6064, 0x00b7पूर्ण, अणु0x607c, 0x00b9पूर्ण,
	अणु0x60af, 0x00b3पूर्ण, अणु0x6097, 0x00b4पूर्ण, अणु0x60ff, 0x00b5पूर्ण, अणु0x60c5, 0x00b0पूर्ण,
	अणु0x6094, 0x00b1पूर्ण, अणु0x600f, 0x00b2पूर्ण, अणु0x605c, 0x00c4पूर्ण, अणु0x6000, 0x00a8पूर्ण,
	अणु0x60c8, 0x00c0पूर्ण, अणु0x6096, 0x00c1पूर्ण, अणु0x601d, 0x0086पूर्ण, अणु0x6000, 0x0050पूर्ण,
	अणु0x6090, 0x0051पूर्ण, अणु0x6018, 0x0052पूर्ण, अणु0x6000, 0x0053पूर्ण, अणु0x6000, 0x0054पूर्ण,
	अणु0x6088, 0x0055पूर्ण, अणु0x6000, 0x0057पूर्ण, अणु0x6090, 0x005aपूर्ण, अणु0x6018, 0x005bपूर्ण,
	अणु0x6005, 0x005cपूर्ण, अणु0x60ed, 0x00c3पूर्ण, अणु0x6000, 0x007fपूर्ण, अणु0x6005, 0x00daपूर्ण,
	अणु0x601f, 0x00e5पूर्ण, अणु0x6067, 0x00e1पूर्ण, अणु0x6000, 0x00e0पूर्ण, अणु0x60ff, 0x00ddपूर्ण,
	अणु0x6000, 0x0005पूर्ण, अणु0x6001, 0x00ffपूर्ण, अणु0x6000, 0x0000पूर्ण, अणु0x6000, 0x0045पूर्ण,
	अणु0x6000, 0x0010पूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_sensor_settings_common1[] = अणु
	अणु0x0041, 0x0000पूर्ण, अणु0x006a, 0x0007पूर्ण, अणु0x00ef, 0x0006पूर्ण, अणु0x006a, 0x000dपूर्ण,
	अणु0x0000, 0x00c0पूर्ण, अणु0x0010, 0x0010पूर्ण, अणु0x0001, 0x00c1पूर्ण, अणु0x0041, 0x00c2पूर्ण,
	अणु0x0004, 0x00d8पूर्ण, अणु0x0012, 0x0004पूर्ण, अणु0x0000, 0x0058पूर्ण, अणु0x0041, 0x0000पूर्ण,
	अणु50, 0xffffपूर्ण,
	अणु0x0061, 0x0000पूर्ण,
	अणु0xffff, 0xffffपूर्ण,
	अणु0x6000, 0x00ffपूर्ण, अणु0x6000, 0x007cपूर्ण, अणु0x6007, 0x007dपूर्ण,
	अणु30, 0xffffपूर्ण,
	अणु0x0040, 0x0000पूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_sensor_settings_common2[] = अणु
	अणु0x6001, 0x00ffपूर्ण, अणु0x6038, 0x000cपूर्ण,
	अणु10, 0xffffपूर्ण,
	अणु0x6000, 0x0011पूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_640[] = अणु
	अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण, अणु0x6067, 0x00e1पूर्ण,
	अणु0x6004, 0x00daपूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण,
	अणु0x6001, 0x00ffपूर्ण, अणु0x6000, 0x0012पूर्ण, अणु0x6000, 0x0011पूर्ण, अणु0x6011, 0x0017पूर्ण,
	अणु0x6075, 0x0018पूर्ण, अणु0x6001, 0x0019पूर्ण, अणु0x6097, 0x001aपूर्ण, अणु0x6036, 0x0032पूर्ण,
	अणु0x60bb, 0x004fपूर्ण, अणु0x6057, 0x005aपूर्ण, अणु0x609c, 0x0050पूर्ण, अणु0x6080, 0x006dपूर्ण,
	अणु0x6092, 0x0026पूर्ण, अणु0x60ff, 0x0020पूर्ण, अणु0x6000, 0x0027पूर्ण, अणु0x6000, 0x00ffपूर्ण,
	अणु0x60c8, 0x00c0पूर्ण, अणु0x6096, 0x00c1पूर्ण, अणु0x6000, 0x008cपूर्ण, अणु0x603d, 0x0086पूर्ण,
	अणु0x6089, 0x0050पूर्ण, अणु0x6090, 0x0051पूर्ण, अणु0x602c, 0x0052पूर्ण, अणु0x6000, 0x0053पूर्ण,
	अणु0x6000, 0x0054पूर्ण, अणु0x6088, 0x0055पूर्ण, अणु0x6000, 0x0057पूर्ण, अणु0x60a0, 0x005aपूर्ण,
	अणु0x6078, 0x005bपूर्ण, अणु0x6000, 0x005cपूर्ण, अणु0x6004, 0x00d3पूर्ण, अणु0x6000, 0x00e0पूर्ण,
	अणु0x60ff, 0x00ddपूर्ण, अणु0x60a1, 0x005aपूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_800[] = अणु
	अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण, अणु0x6067, 0x00e1पूर्ण,
	अणु0x6004, 0x00daपूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण,
	अणु0x6001, 0x00ffपूर्ण, अणु0x6040, 0x0012पूर्ण, अणु0x6000, 0x0011पूर्ण, अणु0x6011, 0x0017पूर्ण,
	अणु0x6043, 0x0018पूर्ण, अणु0x6000, 0x0019पूर्ण, अणु0x604b, 0x001aपूर्ण, अणु0x6009, 0x0032पूर्ण,
	अणु0x60ca, 0x004fपूर्ण, अणु0x60a8, 0x0050पूर्ण, अणु0x6000, 0x006dपूर्ण, अणु0x6038, 0x003dपूर्ण,
	अणु0x60c8, 0x0035पूर्ण, अणु0x6000, 0x0022पूर्ण, अणु0x6092, 0x0026पूर्ण, अणु0x60ff, 0x0020पूर्ण,
	अणु0x6000, 0x0027पूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x6064, 0x00c0पूर्ण, अणु0x604b, 0x00c1पूर्ण,
	अणु0x6000, 0x008cपूर्ण, अणु0x601d, 0x0086पूर्ण, अणु0x6082, 0x00d3पूर्ण, अणु0x6000, 0x00e0पूर्ण,
	अणु0x60ff, 0x00ddपूर्ण, अणु0x6020, 0x008cपूर्ण, अणु0x6001, 0x00ffपूर्ण, अणु0x6044, 0x0018पूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_big1[] = अणु
	अणु0x0002, 0x00c1पूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण,
	अणु0x6001, 0x00ffपूर्ण, अणु0x6000, 0x0012पूर्ण, अणु0x6000, 0x0000पूर्ण, अणु0x6000, 0x0045पूर्ण,
	अणु0x6000, 0x0010पूर्ण, अणु0x6000, 0x0011पूर्ण, अणु0x6011, 0x0017पूर्ण, अणु0x6075, 0x0018पूर्ण,
	अणु0x6001, 0x0019पूर्ण, अणु0x6097, 0x001aपूर्ण, अणु0x6036, 0x0032पूर्ण, अणु0x60bb, 0x004fपूर्ण,
	अणु0x609c, 0x0050पूर्ण, अणु0x6057, 0x005aपूर्ण, अणु0x6080, 0x006dपूर्ण, अणु0x6043, 0x000fपूर्ण,
	अणु0x608f, 0x0003पूर्ण, अणु0x6005, 0x007cपूर्ण, अणु0x6081, 0x0026पूर्ण, अणु0x6000, 0x00ffपूर्ण,
	अणु0x60c8, 0x00c0पूर्ण, अणु0x6096, 0x00c1पूर्ण, अणु0x6000, 0x008cपूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_big2[] = अणु
	अणु0x603d, 0x0086पूर्ण, अणु0x6000, 0x0050पूर्ण, अणु0x6090, 0x0051पूर्ण, अणु0x602c, 0x0052पूर्ण,
	अणु0x6000, 0x0053पूर्ण, अणु0x6000, 0x0054पूर्ण, अणु0x6088, 0x0055पूर्ण, अणु0x6000, 0x0057पूर्ण,
	अणु0x6040, 0x005aपूर्ण, अणु0x60f0, 0x005bपूर्ण, अणु0x6001, 0x005cपूर्ण, अणु0x6082, 0x00d3पूर्ण,
	अणु0x6000, 0x008eपूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_big3[] = अणु
	अणु0x6004, 0x00daपूर्ण, अणु0x6000, 0x00e0पूर्ण, अणु0x6067, 0x00e1पूर्ण, अणु0x60ff, 0x00ddपूर्ण,
	अणु0x6001, 0x00ffपूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x60f1, 0x00ddपूर्ण, अणु0x6004, 0x00e0पूर्ण,
	अणु0x6001, 0x00ffपूर्ण, अणु0x6000, 0x0011पूर्ण, अणु0x6000, 0x00ffपूर्ण, अणु0x6010, 0x00c7पूर्ण,
	अणु0x6000, 0x0092पूर्ण, अणु0x6006, 0x0093पूर्ण, अणु0x60e3, 0x0093पूर्ण, अणु0x6005, 0x0093पूर्ण,
	अणु0x6005, 0x0093पूर्ण, अणु0x60ed, 0x00c3पूर्ण, अणु0x6000, 0x00a4पूर्ण, अणु0x60d0, 0x0087पूर्ण,
	अणु0x6003, 0x0096पूर्ण, अणु0x600c, 0x0097पूर्ण, अणु0x6024, 0x0097पूर्ण, अणु0x6030, 0x0097पूर्ण,
	अणु0x6028, 0x0097पूर्ण, अणु0x6026, 0x0097पूर्ण, अणु0x6002, 0x0097पूर्ण, अणु0x6001, 0x00ffपूर्ण,
	अणु0x6043, 0x000fपूर्ण, अणु0x608f, 0x0003पूर्ण, अणु0x6000, 0x002dपूर्ण, अणु0x6000, 0x002eपूर्ण,
	अणु0x600a, 0x0022पूर्ण, अणु0x6002, 0x0070पूर्ण, अणु0x6008, 0x0014पूर्ण, अणु0x6048, 0x0014पूर्ण,
	अणु0x6000, 0x00ffपूर्ण, अणु0x6000, 0x00e0पूर्ण, अणु0x60ff, 0x00ddपूर्ण,
पूर्ण;

अटल काष्ठा validx tbl_post_unset_alt[] = अणु
	अणु0x006a, 0x000dपूर्ण, अणु0x6001, 0x00ffपूर्ण, अणु0x6081, 0x0026पूर्ण, अणु0x6000, 0x0000पूर्ण,
	अणु0x6000, 0x0045पूर्ण, अणु0x6000, 0x0010पूर्ण, अणु0x6068, 0x000dपूर्ण,
	अणु50, 0xffffपूर्ण,
	अणु0x0021, 0x0000पूर्ण,
पूर्ण;

अटल पूर्णांक  ov2640_init_at_startup(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  ov2640_configure_alt(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  ov2640_init_pre_alt(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  ov2640_init_post_alt(काष्ठा gspca_dev *gspca_dev);
अटल व्योम ov2640_post_unset_alt(काष्ठा gspca_dev *gspca_dev);
अटल पूर्णांक  ov2640_camera_settings(काष्ठा gspca_dev *gspca_dev);
/*==========================================================================*/

व्योम ov2640_init_settings(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	sd->vcur.backlight  =  32;
	sd->vcur.brightness =   0;
	sd->vcur.sharpness  =   6;
	sd->vcur.contrast   =   0;
	sd->vcur.gamma      =  32;
	sd->vcur.hue        =   0;
	sd->vcur.saturation = 128;
	sd->vcur.whitebal   =  64;
	sd->vcur.mirror     =   0;
	sd->vcur.flip       =   0;

	sd->vmax.backlight  =  64;
	sd->vmax.brightness = 255;
	sd->vmax.sharpness  =  31;
	sd->vmax.contrast   = 255;
	sd->vmax.gamma      =  64;
	sd->vmax.hue        = 254 + 2;
	sd->vmax.saturation = 255;
	sd->vmax.whitebal   = 128;
	sd->vmax.mirror     = 1;
	sd->vmax.flip       = 1;
	sd->vmax.AC50Hz     = 0;

	sd->dev_camera_settings = ov2640_camera_settings;
	sd->dev_init_at_startup = ov2640_init_at_startup;
	sd->dev_configure_alt   = ov2640_configure_alt;
	sd->dev_init_pre_alt    = ov2640_init_pre_alt;
	sd->dev_post_unset_alt  = ov2640_post_unset_alt;
पूर्ण

/*==========================================================================*/

अटल व्योम common(काष्ठा gspca_dev *gspca_dev)
अणु
	fetch_validx(gspca_dev, tbl_common, ARRAY_SIZE(tbl_common));
पूर्ण

अटल पूर्णांक ov2640_init_at_startup(काष्ठा gspca_dev *gspca_dev)
अणु
	fetch_validx(gspca_dev, tbl_init_at_startup,
			ARRAY_SIZE(tbl_init_at_startup));

	ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, dat_init1);

	common(gspca_dev);

	ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0006, 1, c61);

	ctrl_out(gspca_dev, 0x40, 1, 0x00ef, 0x0006, 0, शून्य);

	ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, c51);

	ctrl_out(gspca_dev, 0x40, 1, 0x0051, 0x0000, 0, शून्य);
/*	ctrl_out(gspca_dev, 0x40, 11, 0x0000, 0x0000, 0, शून्य); */

	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_init_pre_alt(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	sd->mirrorMask = 0;

	sd->vold.backlight  = -1;
	sd->vold.brightness = -1;
	sd->vold.sharpness  = -1;
	sd->vold.contrast   = -1;
	sd->vold.saturation = -1;
	sd->vold.gamma    = -1;
	sd->vold.hue      = -1;
	sd->vold.whitebal = -1;
	sd->vold.mirror = -1;
	sd->vold.flip   = -1;

	ov2640_init_post_alt(gspca_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_init_post_alt(काष्ठा gspca_dev *gspca_dev)
अणु
	s32 reso = gspca_dev->cam.cam_mode[(s32) gspca_dev->curr_mode].priv;
	s32 n; /* reserved क्रम FETCH functions */

	ctrl_out(gspca_dev, 0x40, 5, 0x0001, 0x0000, 0, शून्य);

	n = fetch_validx(gspca_dev, tbl_sensor_settings_common1,
			ARRAY_SIZE(tbl_sensor_settings_common1));
	ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, dat_post);
	common(gspca_dev);
	keep_on_fetching_validx(gspca_dev, tbl_sensor_settings_common1,
				ARRAY_SIZE(tbl_sensor_settings_common1), n);

	चयन (reso) अणु
	हाल IMAGE_640:
		n = fetch_validx(gspca_dev, tbl_640, ARRAY_SIZE(tbl_640));
		ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, dat_640);
		अवरोध;

	हाल IMAGE_800:
		n = fetch_validx(gspca_dev, tbl_800, ARRAY_SIZE(tbl_800));
		ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200, 12, dat_800);
		अवरोध;

	हाल IMAGE_1600:
	हाल IMAGE_1280:
		n = fetch_validx(gspca_dev, tbl_big1, ARRAY_SIZE(tbl_big1));

		अगर (reso == IMAGE_1280) अणु
			n = fetch_validx(gspca_dev, tbl_big2,
					ARRAY_SIZE(tbl_big2));
		पूर्ण अन्यथा अणु
			ctrl_out(gspca_dev, 0x40, 1, 0x601d, 0x0086, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00d7, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 1, 0x6082, 0x00d3, 0, शून्य);
		पूर्ण

		n = fetch_validx(gspca_dev, tbl_big3, ARRAY_SIZE(tbl_big3));

		अगर (reso == IMAGE_1280) अणु
			ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200,
					12, dat_1280);
		पूर्ण अन्यथा अणु
			ctrl_out(gspca_dev, 0x40, 1, 0x6020, 0x008c, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 1, 0x6076, 0x0018, 0, शून्य);
			ctrl_out(gspca_dev, 0x40, 3, 0x0000, 0x0200,
					12, dat_1600);
		पूर्ण
		अवरोध;
	पूर्ण

	n = fetch_validx(gspca_dev, tbl_sensor_settings_common2,
			ARRAY_SIZE(tbl_sensor_settings_common2));

	ov2640_camera_settings(gspca_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_configure_alt(काष्ठा gspca_dev *gspca_dev)
अणु
	s32 reso = gspca_dev->cam.cam_mode[(s32) gspca_dev->curr_mode].priv;

	चयन (reso) अणु
	हाल IMAGE_640:
		gspca_dev->alt = 3 + 1;
		अवरोध;

	हाल IMAGE_800:
	हाल IMAGE_1280:
	हाल IMAGE_1600:
		gspca_dev->alt = 1 + 1;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ov2640_camera_settings(काष्ठा gspca_dev *gspca_dev)
अणु
	काष्ठा sd *sd = (काष्ठा sd *) gspca_dev;

	s32 backlight = sd->vcur.backlight;
	s32 bright = sd->vcur.brightness;
	s32 sharp  = sd->vcur.sharpness;
	s32 gam    = sd->vcur.gamma;
	s32 cntr   = sd->vcur.contrast;
	s32 sat    = sd->vcur.saturation;
	s32 hue    = sd->vcur.hue;
	s32 wbal   = sd->vcur.whitebal;
	s32 mirror = (((sd->vcur.mirror > 0) ^ sd->mirrorMask) == 0);
	s32 flip   = (((sd->vcur.flip   > 0) ^ sd->mirrorMask) == 0);

	अगर (backlight != sd->vold.backlight) अणु
		/* No sd->vold.backlight=backlight; (to be करोne again later) */
		अगर (backlight < 0 || backlight > sd->vmax.backlight)
			backlight = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6001                 , 0x00ff,
				0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight     , 0x0024,
				0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight - 10, 0x0025,
				0, शून्य);
	पूर्ण

	अगर (bright != sd->vold.brightness) अणु
		sd->vold.brightness = bright;
		अगर (bright < 0 || bright > sd->vmax.brightness)
			bright = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000         , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6009         , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + bright, 0x007d, 0, शून्य);
	पूर्ण

	अगर (wbal != sd->vold.whitebal) अणु
		sd->vold.whitebal = wbal;
		अगर (wbal < 0 || wbal > sd->vmax.whitebal)
			wbal = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000       , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6003       , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + wbal, 0x007d, 0, शून्य);
	पूर्ण

	अगर (cntr != sd->vold.contrast) अणु
		sd->vold.contrast = cntr;
		अगर (cntr < 0 || cntr > sd->vmax.contrast)
			cntr = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000       , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6007       , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + cntr, 0x007d, 0, शून्य);
	पूर्ण

	अगर (sat != sd->vold.saturation) अणु
		sd->vold.saturation = sat;
		अगर (sat < 0 || sat > sd->vmax.saturation)
			sat = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000      , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6001      , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + sat, 0x007d, 0, शून्य);
	पूर्ण

	अगर (sharp != sd->vold.sharpness) अणु
		sd->vold.sharpness = sharp;
		अगर (sharp < 0 || sharp > sd->vmax.sharpness)
			sharp = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000        , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6001        , 0x0092, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x60c0 + sharp, 0x0093, 0, शून्य);
	पूर्ण

	अगर (hue != sd->vold.hue) अणु
		sd->vold.hue = hue;
		अगर (hue < 0 || hue > sd->vmax.hue)
			hue = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000     , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6002     , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + hue * (hue < 255), 0x007d,
				0, शून्य);
		अगर (hue >= 255)
			sd->swapRB = 1;
		अन्यथा
			sd->swapRB = 0;
	पूर्ण

	अगर (gam != sd->vold.gamma) अणु
		sd->vold.gamma = gam;
		अगर (gam < 0 || gam > sd->vmax.gamma)
			gam = 0;

		ctrl_out(gspca_dev, 0x40, 1, 0x6000      , 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6008      , 0x007c, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000 + gam, 0x007d, 0, शून्य);
	पूर्ण

	अगर (mirror != sd->vold.mirror || flip != sd->vold.flip) अणु
		sd->vold.mirror = mirror;
		sd->vold.flip   = flip;

		mirror = 0x80 * mirror;
		ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000, 0x8004, 0, शून्य);
		ctrl_in(gspca_dev, 0xc0, 2, 0x6000, 0x8004, 1, c28);
		ctrl_out(gspca_dev, 0x40, 1, 0x6028 + mirror, 0x0004, 0, शून्य);

		flip = 0x50 * flip + mirror;
		ctrl_out(gspca_dev, 0x40, 1, 0x6001, 0x00ff, 0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x6000, 0x8004, 0, शून्य);
		ctrl_in(gspca_dev, 0xc0, 2, 0x6000, 0x8004, 1, ca8);
		ctrl_out(gspca_dev, 0x40, 1, 0x6028 + flip, 0x0004, 0, शून्य);

		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, c50);
	पूर्ण

	अगर (backlight != sd->vold.backlight) अणु
		sd->vold.backlight = backlight;

		ctrl_out(gspca_dev, 0x40, 1, 0x6001                 , 0x00ff,
				0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight     , 0x0024,
				0, शून्य);
		ctrl_out(gspca_dev, 0x40, 1, 0x601e + backlight - 10, 0x0025,
				0, शून्य);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ov2640_post_unset_alt(काष्ठा gspca_dev *gspca_dev)
अणु
	ctrl_out(gspca_dev, 0x40, 5, 0x0000, 0x0000, 0, शून्य);
	msleep(20);
	fetch_validx(gspca_dev, tbl_post_unset_alt,
			ARRAY_SIZE(tbl_post_unset_alt));
पूर्ण
