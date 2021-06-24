<शैली गुरु>
/*
 * Copyright 2012 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Ben Skeggs
 */
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/bit.h>
#समावेश <subdev/bios/bmp.h>
#समावेश <subdev/bios/conn.h>
#समावेश <subdev/bios/dcb.h>
#समावेश <subdev/bios/dp.h>
#समावेश <subdev/bios/gpपन.स>
#समावेश <subdev/bios/init.h>
#समावेश <subdev/bios/ramcfg.h>

#समावेश <subdev/devinit.h>
#समावेश <subdev/gpपन.स>
#समावेश <subdev/i2c.h>
#समावेश <subdev/vga.h>

#समावेश <linux/kernel.h>

#घोषणा bioslog(lvl, fmt, args...) करो अणु                                        \
	nvkm_prपूर्णांकk(init->subdev, lvl, info, "0x%08x[%c]: "fmt,                \
		    init->offset, init_exec(init) ?                            \
		    '0' + (init->nested - 1) : ' ', ##args);                   \
पूर्ण जबतक(0)
#घोषणा cont(fmt, args...) करो अणु                                                \
	अगर (init->subdev->debug >= NV_DBG_TRACE)                               \
		prपूर्णांकk(fmt, ##args);                                           \
पूर्ण जबतक(0)
#घोषणा trace(fmt, args...) bioslog(TRACE, fmt, ##args)
#घोषणा warn(fmt, args...) bioslog(WARN, fmt, ##args)
#घोषणा error(fmt, args...) bioslog(ERROR, fmt, ##args)

/******************************************************************************
 * init parser control flow helpers
 *****************************************************************************/

अटल अंतरभूत bool
init_exec(काष्ठा nvbios_init *init)
अणु
	वापस (init->execute == 1) || ((init->execute & 5) == 5);
पूर्ण

अटल अंतरभूत व्योम
init_exec_set(काष्ठा nvbios_init *init, bool exec)
अणु
	अगर (exec) init->execute &= 0xfd;
	अन्यथा      init->execute |= 0x02;
पूर्ण

अटल अंतरभूत व्योम
init_exec_inv(काष्ठा nvbios_init *init)
अणु
	init->execute ^= 0x02;
पूर्ण

अटल अंतरभूत व्योम
init_exec_क्रमce(काष्ठा nvbios_init *init, bool exec)
अणु
	अगर (exec) init->execute |= 0x04;
	अन्यथा      init->execute &= 0xfb;
पूर्ण

/******************************************************************************
 * init parser wrappers क्रम normal रेजिस्टर/i2c/whatever accessors
 *****************************************************************************/

अटल अंतरभूत पूर्णांक
init_or(काष्ठा nvbios_init *init)
अणु
	अगर (init_exec(init)) अणु
		अगर (init->or >= 0)
			वापस init->or;
		error("script needs OR!!\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
init_link(काष्ठा nvbios_init *init)
अणु
	अगर (init_exec(init)) अणु
		अगर (init->link)
			वापस init->link == 2;
		error("script needs OR link\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
init_head(काष्ठा nvbios_init *init)
अणु
	अगर (init_exec(init)) अणु
		अगर (init->head >= 0)
			वापस init->head;
		error("script needs head\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल u8
init_conn(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	काष्ठा nvbios_connE connE;
	u8  ver, hdr;
	u32 conn;

	अगर (init_exec(init)) अणु
		अगर (init->outp) अणु
			conn = init->outp->connector;
			conn = nvbios_connEp(bios, conn, &ver, &hdr, &connE);
			अगर (conn)
				वापस connE.type;
		पूर्ण

		error("script needs connector type\n");
	पूर्ण

	वापस 0xff;
पूर्ण

अटल अंतरभूत u32
init_nvreg(काष्ठा nvbios_init *init, u32 reg)
अणु
	काष्ठा nvkm_devinit *devinit = init->subdev->device->devinit;

	/* C51 (at least) someबार has the lower bits set which the VBIOS
	 * पूर्णांकerprets to mean that access needs to go through certain IO
	 * ports instead.  The NVIDIA binary driver has been seen to access
	 * these through the NV रेजिस्टर address, so lets assume we can
	 * करो the same
	 */
	reg &= ~0x00000003;

	/* GF8+ display scripts need रेजिस्टर addresses mangled a bit to
	 * select a specअगरic CRTC/OR
	 */
	अगर (init->subdev->device->card_type >= NV_50) अणु
		अगर (reg & 0x80000000) अणु
			reg += init_head(init) * 0x800;
			reg &= ~0x80000000;
		पूर्ण

		अगर (reg & 0x40000000) अणु
			reg += init_or(init) * 0x800;
			reg &= ~0x40000000;
			अगर (reg & 0x20000000) अणु
				reg += init_link(init) * 0x80;
				reg &= ~0x20000000;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (reg & ~0x00fffffc)
		warn("unknown bits in register 0x%08x\n", reg);

	वापस nvkm_devinit_mmio(devinit, reg);
पूर्ण

अटल u32
init_rd32(काष्ठा nvbios_init *init, u32 reg)
अणु
	काष्ठा nvkm_device *device = init->subdev->device;
	reg = init_nvreg(init, reg);
	अगर (reg != ~0 && init_exec(init))
		वापस nvkm_rd32(device, reg);
	वापस 0x00000000;
पूर्ण

अटल व्योम
init_wr32(काष्ठा nvbios_init *init, u32 reg, u32 val)
अणु
	काष्ठा nvkm_device *device = init->subdev->device;
	reg = init_nvreg(init, reg);
	अगर (reg != ~0 && init_exec(init))
		nvkm_wr32(device, reg, val);
पूर्ण

अटल u32
init_mask(काष्ठा nvbios_init *init, u32 reg, u32 mask, u32 val)
अणु
	काष्ठा nvkm_device *device = init->subdev->device;
	reg = init_nvreg(init, reg);
	अगर (reg != ~0 && init_exec(init)) अणु
		u32 पंचांगp = nvkm_rd32(device, reg);
		nvkm_wr32(device, reg, (पंचांगp & ~mask) | val);
		वापस पंचांगp;
	पूर्ण
	वापस 0x00000000;
पूर्ण

अटल u8
init_rdport(काष्ठा nvbios_init *init, u16 port)
अणु
	अगर (init_exec(init))
		वापस nvkm_rdport(init->subdev->device, init->head, port);
	वापस 0x00;
पूर्ण

अटल व्योम
init_wrport(काष्ठा nvbios_init *init, u16 port, u8 value)
अणु
	अगर (init_exec(init))
		nvkm_wrport(init->subdev->device, init->head, port, value);
पूर्ण

अटल u8
init_rdvgai(काष्ठा nvbios_init *init, u16 port, u8 index)
अणु
	काष्ठा nvkm_subdev *subdev = init->subdev;
	अगर (init_exec(init)) अणु
		पूर्णांक head = init->head < 0 ? 0 : init->head;
		वापस nvkm_rdvgai(subdev->device, head, port, index);
	पूर्ण
	वापस 0x00;
पूर्ण

अटल व्योम
init_wrvgai(काष्ठा nvbios_init *init, u16 port, u8 index, u8 value)
अणु
	काष्ठा nvkm_device *device = init->subdev->device;

	/* क्रमce head 0 क्रम updates to cr44, it only exists on first head */
	अगर (device->card_type < NV_50) अणु
		अगर (port == 0x03d4 && index == 0x44)
			init->head = 0;
	पूर्ण

	अगर (init_exec(init)) अणु
		पूर्णांक head = init->head < 0 ? 0 : init->head;
		nvkm_wrvgai(device, head, port, index, value);
	पूर्ण

	/* select head 1 अगर cr44 ग_लिखो selected it */
	अगर (device->card_type < NV_50) अणु
		अगर (port == 0x03d4 && index == 0x44 && value == 3)
			init->head = 1;
	पूर्ण
पूर्ण

अटल काष्ठा i2c_adapter *
init_i2c(काष्ठा nvbios_init *init, पूर्णांक index)
अणु
	काष्ठा nvkm_i2c *i2c = init->subdev->device->i2c;
	काष्ठा nvkm_i2c_bus *bus;

	अगर (index == 0xff) अणु
		index = NVKM_I2C_BUS_PRI;
		अगर (init->outp && init->outp->i2c_upper_शेष)
			index = NVKM_I2C_BUS_SEC;
	पूर्ण अन्यथा
	अगर (index == 0x80) अणु
		index = NVKM_I2C_BUS_PRI;
	पूर्ण अन्यथा
	अगर (index == 0x81) अणु
		index = NVKM_I2C_BUS_SEC;
	पूर्ण

	bus = nvkm_i2c_bus_find(i2c, index);
	वापस bus ? &bus->i2c : शून्य;
पूर्ण

अटल पूर्णांक
init_rdi2cr(काष्ठा nvbios_init *init, u8 index, u8 addr, u8 reg)
अणु
	काष्ठा i2c_adapter *adap = init_i2c(init, index);
	अगर (adap && init_exec(init))
		वापस nvkm_rdi2cr(adap, addr, reg);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक
init_wri2cr(काष्ठा nvbios_init *init, u8 index, u8 addr, u8 reg, u8 val)
अणु
	काष्ठा i2c_adapter *adap = init_i2c(init, index);
	अगर (adap && init_exec(init))
		वापस nvkm_wri2cr(adap, addr, reg, val);
	वापस -ENODEV;
पूर्ण

अटल काष्ठा nvkm_i2c_aux *
init_aux(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_i2c *i2c = init->subdev->device->i2c;
	अगर (!init->outp) अणु
		अगर (init_exec(init))
			error("script needs output for aux\n");
		वापस शून्य;
	पूर्ण
	वापस nvkm_i2c_aux_find(i2c, init->outp->i2c_index);
पूर्ण

अटल u8
init_rdauxr(काष्ठा nvbios_init *init, u32 addr)
अणु
	काष्ठा nvkm_i2c_aux *aux = init_aux(init);
	u8 data;

	अगर (aux && init_exec(init)) अणु
		पूर्णांक ret = nvkm_rdaux(aux, addr, &data, 1);
		अगर (ret == 0)
			वापस data;
		trace("auxch read failed with %d\n", ret);
	पूर्ण

	वापस 0x00;
पूर्ण

अटल पूर्णांक
init_wrauxr(काष्ठा nvbios_init *init, u32 addr, u8 data)
अणु
	काष्ठा nvkm_i2c_aux *aux = init_aux(init);
	अगर (aux && init_exec(init)) अणु
		पूर्णांक ret = nvkm_wraux(aux, addr, &data, 1);
		अगर (ret)
			trace("auxch write failed with %d\n", ret);
		वापस ret;
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल व्योम
init_prog_pll(काष्ठा nvbios_init *init, u32 id, u32 freq)
अणु
	काष्ठा nvkm_devinit *devinit = init->subdev->device->devinit;
	अगर (init_exec(init)) अणु
		पूर्णांक ret = nvkm_devinit_pll_set(devinit, id, freq);
		अगर (ret)
			warn("failed to prog pll 0x%08x to %dkHz\n", id, freq);
	पूर्ण
पूर्ण

/******************************************************************************
 * parsing of bios काष्ठाures that are required to execute init tables
 *****************************************************************************/

अटल u16
init_table(काष्ठा nvkm_bios *bios, u16 *len)
अणु
	काष्ठा bit_entry bit_I;

	अगर (!bit_entry(bios, 'I', &bit_I)) अणु
		*len = bit_I.length;
		वापस bit_I.offset;
	पूर्ण

	अगर (bmp_version(bios) >= 0x0510) अणु
		*len = 14;
		वापस bios->bmp_offset + 75;
	पूर्ण

	वापस 0x0000;
पूर्ण

अटल u16
init_table_(काष्ठा nvbios_init *init, u16 offset, स्थिर अक्षर *name)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 len, data = init_table(bios, &len);
	अगर (data) अणु
		अगर (len >= offset + 2) अणु
			data = nvbios_rd16(bios, data + offset);
			अगर (data)
				वापस data;

			warn("%s pointer invalid\n", name);
			वापस 0x0000;
		पूर्ण

		warn("init data too short for %s pointer", name);
		वापस 0x0000;
	पूर्ण

	warn("init data not found\n");
	वापस 0x0000;
पूर्ण

#घोषणा init_script_table(b) init_table_((b), 0x00, "script table")
#घोषणा init_macro_index_table(b) init_table_((b), 0x02, "macro index table")
#घोषणा init_macro_table(b) init_table_((b), 0x04, "macro table")
#घोषणा init_condition_table(b) init_table_((b), 0x06, "condition table")
#घोषणा init_io_condition_table(b) init_table_((b), 0x08, "io condition table")
#घोषणा init_io_flag_condition_table(b) init_table_((b), 0x0a, "io flag conditon table")
#घोषणा init_function_table(b) init_table_((b), 0x0c, "function table")
#घोषणा init_xlat_table(b) init_table_((b), 0x10, "xlat table");

अटल u16
init_script(काष्ठा nvkm_bios *bios, पूर्णांक index)
अणु
	काष्ठा nvbios_init init = अणु .subdev = &bios->subdev पूर्ण;
	u16 bmp_ver = bmp_version(bios), data;

	अगर (bmp_ver && bmp_ver < 0x0510) अणु
		अगर (index > 1 || bmp_ver < 0x0100)
			वापस 0x0000;

		data = bios->bmp_offset + (bmp_ver < 0x0200 ? 14 : 18);
		वापस nvbios_rd16(bios, data + (index * 2));
	पूर्ण

	data = init_script_table(&init);
	अगर (data)
		वापस nvbios_rd16(bios, data + (index * 2));

	वापस 0x0000;
पूर्ण

अटल u16
init_unknown_script(काष्ठा nvkm_bios *bios)
अणु
	u16 len, data = init_table(bios, &len);
	अगर (data && len >= 16)
		वापस nvbios_rd16(bios, data + 14);
	वापस 0x0000;
पूर्ण

अटल u8
init_ram_restrict_group_count(काष्ठा nvbios_init *init)
अणु
	वापस nvbios_ramcfg_count(init->subdev->device->bios);
पूर्ण

अटल u8
init_ram_restrict(काष्ठा nvbios_init *init)
अणु
	/* This appears to be the behaviour of the VBIOS parser, and *is*
	 * important to cache the NV_PEXTDEV_BOOT0 on later chipsets to
	 * aव्योम fucking up the memory controller (somehow) by पढ़ोing it
	 * on every INIT_RAM_RESTRICT_ZM_GROUP opcode.
	 *
	 * Preserving the non-caching behaviour on earlier chipsets just
	 * in हाल *not* re-पढ़ोing the strap causes similar अवरोधage.
	 */
	अगर (!init->ramcfg || init->subdev->device->bios->version.major < 0x70)
		init->ramcfg = 0x80000000 | nvbios_ramcfg_index(init->subdev);
	वापस (init->ramcfg & 0x7fffffff);
पूर्ण

अटल u8
init_xlat_(काष्ठा nvbios_init *init, u8 index, u8 offset)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_xlat_table(init);
	अगर (table) अणु
		u16 data = nvbios_rd16(bios, table + (index * 2));
		अगर (data)
			वापस nvbios_rd08(bios, data + offset);
		warn("xlat table pointer %d invalid\n", index);
	पूर्ण
	वापस 0x00;
पूर्ण

/******************************************************************************
 * utility functions used by various init opcode handlers
 *****************************************************************************/

अटल bool
init_condition_met(काष्ठा nvbios_init *init, u8 cond)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_condition_table(init);
	अगर (table) अणु
		u32 reg = nvbios_rd32(bios, table + (cond * 12) + 0);
		u32 msk = nvbios_rd32(bios, table + (cond * 12) + 4);
		u32 val = nvbios_rd32(bios, table + (cond * 12) + 8);
		trace("\t[0x%02x] (R[0x%06x] & 0x%08x) == 0x%08x\n",
		      cond, reg, msk, val);
		वापस (init_rd32(init, reg) & msk) == val;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
init_io_condition_met(काष्ठा nvbios_init *init, u8 cond)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_io_condition_table(init);
	अगर (table) अणु
		u16 port = nvbios_rd16(bios, table + (cond * 5) + 0);
		u8 index = nvbios_rd08(bios, table + (cond * 5) + 2);
		u8  mask = nvbios_rd08(bios, table + (cond * 5) + 3);
		u8 value = nvbios_rd08(bios, table + (cond * 5) + 4);
		trace("\t[0x%02x] (0x%04x[0x%02x] & 0x%02x) == 0x%02x\n",
		      cond, port, index, mask, value);
		वापस (init_rdvgai(init, port, index) & mask) == value;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
init_io_flag_condition_met(काष्ठा nvbios_init *init, u8 cond)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 table = init_io_flag_condition_table(init);
	अगर (table) अणु
		u16 port = nvbios_rd16(bios, table + (cond * 9) + 0);
		u8 index = nvbios_rd08(bios, table + (cond * 9) + 2);
		u8  mask = nvbios_rd08(bios, table + (cond * 9) + 3);
		u8 shअगरt = nvbios_rd08(bios, table + (cond * 9) + 4);
		u16 data = nvbios_rd16(bios, table + (cond * 9) + 5);
		u8 dmask = nvbios_rd08(bios, table + (cond * 9) + 7);
		u8 value = nvbios_rd08(bios, table + (cond * 9) + 8);
		u8 ioval = (init_rdvgai(init, port, index) & mask) >> shअगरt;
		वापस (nvbios_rd08(bios, data + ioval) & dmask) == value;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत u32
init_shअगरt(u32 data, u8 shअगरt)
अणु
	अगर (shअगरt < 0x80)
		वापस data >> shअगरt;
	वापस data << (0x100 - shअगरt);
पूर्ण

अटल u32
init_पंचांगds_reg(काष्ठा nvbios_init *init, u8 पंचांगds)
अणु
	/* For mlv < 0x80, it is an index पूर्णांकo a table of TMDS base addresses.
	 * For mlv == 0x80 use the "or" value of the dcb_entry indexed by
	 * CR58 क्रम CR57 = 0 to index a table of offsets to the basic
	 * 0x6808b0 address.
	 * For mlv == 0x81 use the "or" value of the dcb_entry indexed by
	 * CR58 क्रम CR57 = 0 to index a table of offsets to the basic
	 * 0x6808b0 address, and then flip the offset by 8.
	 */
	स्थिर पूर्णांक pramdac_offset[13] = अणु
		0, 0, 0x8, 0, 0x2000, 0, 0, 0, 0x2008, 0, 0, 0, 0x2000 पूर्ण;
	स्थिर u32 pramdac_table[4] = अणु
		0x6808b0, 0x6808b8, 0x6828b0, 0x6828b8 पूर्ण;

	अगर (पंचांगds >= 0x80) अणु
		अगर (init->outp) अणु
			u32 dacoffset = pramdac_offset[init->outp->or];
			अगर (पंचांगds == 0x81)
				dacoffset ^= 8;
			वापस 0x6808b0 + dacoffset;
		पूर्ण

		अगर (init_exec(init))
			error("tmds opcodes need dcb\n");
	पूर्ण अन्यथा अणु
		अगर (पंचांगds < ARRAY_SIZE(pramdac_table))
			वापस pramdac_table[पंचांगds];

		error("tmds selector 0x%02x unknown\n", पंचांगds);
	पूर्ण

	वापस 0;
पूर्ण

/******************************************************************************
 * init opcode handlers
 *****************************************************************************/

/**
 * init_reserved - stub क्रम various unknown/unused single-byte opcodes
 *
 */
अटल व्योम
init_reserved(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 opcode = nvbios_rd08(bios, init->offset);
	u8 length, i;

	चयन (opcode) अणु
	हाल 0xaa:
		length = 4;
		अवरोध;
	शेष:
		length = 1;
		अवरोध;
	पूर्ण

	trace("RESERVED 0x%02x\t", opcode);
	क्रम (i = 1; i < length; i++)
		cont(" 0x%02x", nvbios_rd08(bios, init->offset + i));
	cont("\n");
	init->offset += length;
पूर्ण

/**
 * INIT_DONE - opcode 0x71
 *
 */
अटल व्योम
init_करोne(काष्ठा nvbios_init *init)
अणु
	trace("DONE\n");
	init->offset = 0x0000;
पूर्ण

/**
 * INIT_IO_RESTRICT_PROG - opcode 0x32
 *
 */
अटल व्योम
init_io_restrict_prog(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd08(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8 shअगरt = nvbios_rd08(bios, init->offset + 5);
	u8 count = nvbios_rd08(bios, init->offset + 6);
	u32  reg = nvbios_rd32(bios, init->offset + 7);
	u8 conf, i;

	trace("IO_RESTRICT_PROG\tR[0x%06x] = "
	      "((0x%04x[0x%02x] & 0x%02x) >> %d) [{\n",
	      reg, port, index, mask, shअगरt);
	init->offset += 11;

	conf = (init_rdvgai(init, port, index) & mask) >> shअगरt;
	क्रम (i = 0; i < count; i++) अणु
		u32 data = nvbios_rd32(bios, init->offset);

		अगर (i == conf) अणु
			trace("\t0x%08x *\n", data);
			init_wr32(init, reg, data);
		पूर्ण अन्यथा अणु
			trace("\t0x%08x\n", data);
		पूर्ण

		init->offset += 4;
	पूर्ण
	trace("}]\n");
पूर्ण

/**
 * INIT_REPEAT - opcode 0x33
 *
 */
अटल व्योम
init_repeat(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 count = nvbios_rd08(bios, init->offset + 1);
	u16 repeat = init->repeat;

	trace("REPEAT\t0x%02x\n", count);
	init->offset += 2;

	init->repeat = init->offset;
	init->repend = init->offset;
	जबतक (count--) अणु
		init->offset = init->repeat;
		nvbios_exec(init);
		अगर (count)
			trace("REPEAT\t0x%02x\n", count);
	पूर्ण
	init->offset = init->repend;
	init->repeat = repeat;
पूर्ण

/**
 * INIT_IO_RESTRICT_PLL - opcode 0x34
 *
 */
अटल व्योम
init_io_restrict_pll(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd08(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8 shअगरt = nvbios_rd08(bios, init->offset + 5);
	s8  iofc = nvbios_rd08(bios, init->offset + 6);
	u8 count = nvbios_rd08(bios, init->offset + 7);
	u32  reg = nvbios_rd32(bios, init->offset + 8);
	u8 conf, i;

	trace("IO_RESTRICT_PLL\tR[0x%06x] =PLL= "
	      "((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) IOFCOND 0x%02x [{\n",
	      reg, port, index, mask, shअगरt, iofc);
	init->offset += 12;

	conf = (init_rdvgai(init, port, index) & mask) >> shअगरt;
	क्रम (i = 0; i < count; i++) अणु
		u32 freq = nvbios_rd16(bios, init->offset) * 10;

		अगर (i == conf) अणु
			trace("\t%dkHz *\n", freq);
			अगर (iofc > 0 && init_io_flag_condition_met(init, iofc))
				freq *= 2;
			init_prog_pll(init, reg, freq);
		पूर्ण अन्यथा अणु
			trace("\t%dkHz\n", freq);
		पूर्ण

		init->offset += 2;
	पूर्ण
	trace("}]\n");
पूर्ण

/**
 * INIT_END_REPEAT - opcode 0x36
 *
 */
अटल व्योम
init_end_repeat(काष्ठा nvbios_init *init)
अणु
	trace("END_REPEAT\n");
	init->offset += 1;

	अगर (init->repeat) अणु
		init->repend = init->offset;
		init->offset = 0;
	पूर्ण
पूर्ण

/**
 * INIT_COPY - opcode 0x37
 *
 */
अटल व्योम
init_copy(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u8 shअगरt = nvbios_rd08(bios, init->offset + 5);
	u8 smask = nvbios_rd08(bios, init->offset + 6);
	u16 port = nvbios_rd16(bios, init->offset + 7);
	u8 index = nvbios_rd08(bios, init->offset + 9);
	u8  mask = nvbios_rd08(bios, init->offset + 10);
	u8  data;

	trace("COPY\t0x%04x[0x%02x] &= 0x%02x |= "
	      "((R[0x%06x] %s 0x%02x) & 0x%02x)\n",
	      port, index, mask, reg, (shअगरt & 0x80) ? "<<" : ">>",
	      (shअगरt & 0x80) ? (0x100 - shअगरt) : shअगरt, smask);
	init->offset += 11;

	data  = init_rdvgai(init, port, index) & mask;
	data |= init_shअगरt(init_rd32(init, reg), shअगरt) & smask;
	init_wrvgai(init, port, index, data);
पूर्ण

/**
 * INIT_NOT - opcode 0x38
 *
 */
अटल व्योम
init_not(काष्ठा nvbios_init *init)
अणु
	trace("NOT\n");
	init->offset += 1;
	init_exec_inv(init);
पूर्ण

/**
 * INIT_IO_FLAG_CONDITION - opcode 0x39
 *
 */
अटल व्योम
init_io_flag_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_rd08(bios, init->offset + 1);

	trace("IO_FLAG_CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	अगर (!init_io_flag_condition_met(init, cond))
		init_exec_set(init, false);
पूर्ण

/**
 * INIT_GENERIC_CONDITION - opcode 0x3a
 *
 */
अटल व्योम
init_generic_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	काष्ठा nvbios_dpout info;
	u8  cond = nvbios_rd08(bios, init->offset + 1);
	u8  size = nvbios_rd08(bios, init->offset + 2);
	u8  ver, hdr, cnt, len;
	u16 data;

	trace("GENERIC_CONDITION\t0x%02x 0x%02x\n", cond, size);
	init->offset += 3;

	चयन (cond) अणु
	हाल 0: /* CONDITION_ID_INT_DP. */
		अगर (init_conn(init) != DCB_CONNECTOR_eDP)
			init_exec_set(init, false);
		अवरोध;
	हाल 1: /* CONDITION_ID_USE_SPPLL0. */
	हाल 2: /* CONDITION_ID_USE_SPPLL1. */
		अगर ( init->outp &&
		    (data = nvbios_dpout_match(bios, DCB_OUTPUT_DP,
					       (init->outp->or << 0) |
					       (init->outp->sorconf.link << 6),
					       &ver, &hdr, &cnt, &len, &info)))
		अणु
			अगर (!(info.flags & cond))
				init_exec_set(init, false);
			अवरोध;
		पूर्ण

		अगर (init_exec(init))
			warn("script needs dp output table data\n");
		अवरोध;
	हाल 5: /* CONDITION_ID_ASSR_SUPPORT. */
		अगर (!(init_rdauxr(init, 0x0d) & 1))
			init_exec_set(init, false);
		अवरोध;
	हाल 7: /* CONDITION_ID_NO_PANEL_SEQ_DELAYS. */
		init_exec_set(init, false);
		अवरोध;
	शेष:
		warn("INIT_GENERIC_CONDITION: unknown 0x%02x\n", cond);
		init->offset += size;
		अवरोध;
	पूर्ण
पूर्ण

/**
 * INIT_IO_MASK_OR - opcode 0x3b
 *
 */
अटल व्योम
init_io_mask_or(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8    or = init_or(init);
	u8  data;

	trace("IO_MASK_OR\t0x03d4[0x%02x] &= ~(1 << 0x%02x)\n", index, or);
	init->offset += 2;

	data = init_rdvgai(init, 0x03d4, index);
	init_wrvgai(init, 0x03d4, index, data &= ~(1 << or));
पूर्ण

/**
 * INIT_IO_OR - opcode 0x3c
 *
 */
अटल व्योम
init_io_or(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8    or = init_or(init);
	u8  data;

	trace("IO_OR\t0x03d4[0x%02x] |= (1 << 0x%02x)\n", index, or);
	init->offset += 2;

	data = init_rdvgai(init, 0x03d4, index);
	init_wrvgai(init, 0x03d4, index, data | (1 << or));
पूर्ण

/**
 * INIT_ANDN_REG - opcode 0x47
 *
 */
अटल व्योम
init_andn_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u32 mask = nvbios_rd32(bios, init->offset + 5);

	trace("ANDN_REG\tR[0x%06x] &= ~0x%08x\n", reg, mask);
	init->offset += 9;

	init_mask(init, reg, mask, 0);
पूर्ण

/**
 * INIT_OR_REG - opcode 0x48
 *
 */
अटल व्योम
init_or_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u32 mask = nvbios_rd32(bios, init->offset + 5);

	trace("OR_REG\tR[0x%06x] |= 0x%08x\n", reg, mask);
	init->offset += 9;

	init_mask(init, reg, 0, mask);
पूर्ण

/**
 * INIT_INDEX_ADDRESS_LATCHED - opcode 0x49
 *
 */
अटल व्योम
init_idx_addr_latched(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 creg = nvbios_rd32(bios, init->offset + 1);
	u32 dreg = nvbios_rd32(bios, init->offset + 5);
	u32 mask = nvbios_rd32(bios, init->offset + 9);
	u32 data = nvbios_rd32(bios, init->offset + 13);
	u8 count = nvbios_rd08(bios, init->offset + 17);

	trace("INDEX_ADDRESS_LATCHED\tR[0x%06x] : R[0x%06x]\n", creg, dreg);
	trace("\tCTRL &= 0x%08x |= 0x%08x\n", mask, data);
	init->offset += 18;

	जबतक (count--) अणु
		u8 iaddr = nvbios_rd08(bios, init->offset + 0);
		u8 idata = nvbios_rd08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", iaddr, idata);
		init->offset += 2;

		init_wr32(init, dreg, idata);
		init_mask(init, creg, ~mask, data | iaddr);
	पूर्ण
पूर्ण

/**
 * INIT_IO_RESTRICT_PLL2 - opcode 0x4a
 *
 */
अटल व्योम
init_io_restrict_pll2(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd08(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8 shअगरt = nvbios_rd08(bios, init->offset + 5);
	u8 count = nvbios_rd08(bios, init->offset + 6);
	u32  reg = nvbios_rd32(bios, init->offset + 7);
	u8  conf, i;

	trace("IO_RESTRICT_PLL2\t"
	      "R[0x%06x] =PLL= ((0x%04x[0x%02x] & 0x%02x) >> 0x%02x) [{\n",
	      reg, port, index, mask, shअगरt);
	init->offset += 11;

	conf = (init_rdvgai(init, port, index) & mask) >> shअगरt;
	क्रम (i = 0; i < count; i++) अणु
		u32 freq = nvbios_rd32(bios, init->offset);
		अगर (i == conf) अणु
			trace("\t%dkHz *\n", freq);
			init_prog_pll(init, reg, freq);
		पूर्ण अन्यथा अणु
			trace("\t%dkHz\n", freq);
		पूर्ण
		init->offset += 4;
	पूर्ण
	trace("}]\n");
पूर्ण

/**
 * INIT_PLL2 - opcode 0x4b
 *
 */
अटल व्योम
init_pll2(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u32 freq = nvbios_rd32(bios, init->offset + 5);

	trace("PLL2\tR[0x%06x] =PLL= %dkHz\n", reg, freq);
	init->offset += 9;

	init_prog_pll(init, reg, freq);
पूर्ण

/**
 * INIT_I2C_BYTE - opcode 0x4c
 *
 */
अटल व्योम
init_i2c_byte(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_rd08(bios, init->offset + 3);

	trace("I2C_BYTE\tI2C[0x%02x][0x%02x]\n", index, addr);
	init->offset += 4;

	जबतक (count--) अणु
		u8  reg = nvbios_rd08(bios, init->offset + 0);
		u8 mask = nvbios_rd08(bios, init->offset + 1);
		u8 data = nvbios_rd08(bios, init->offset + 2);
		पूर्णांक val;

		trace("\t[0x%02x] &= 0x%02x |= 0x%02x\n", reg, mask, data);
		init->offset += 3;

		val = init_rdi2cr(init, index, addr, reg);
		अगर (val < 0)
			जारी;
		init_wri2cr(init, index, addr, reg, (val & mask) | data);
	पूर्ण
पूर्ण

/**
 * INIT_ZM_I2C_BYTE - opcode 0x4d
 *
 */
अटल व्योम
init_zm_i2c_byte(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_rd08(bios, init->offset + 3);

	trace("ZM_I2C_BYTE\tI2C[0x%02x][0x%02x]\n", index, addr);
	init->offset += 4;

	जबतक (count--) अणु
		u8  reg = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", reg, data);
		init->offset += 2;

		init_wri2cr(init, index, addr, reg, data);
	पूर्ण
पूर्ण

/**
 * INIT_ZM_I2C - opcode 0x4e
 *
 */
अटल व्योम
init_zm_i2c(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 count = nvbios_rd08(bios, init->offset + 3);
	u8 data[256], i;

	trace("ZM_I2C\tI2C[0x%02x][0x%02x]\n", index, addr);
	init->offset += 4;

	क्रम (i = 0; i < count; i++) अणु
		data[i] = nvbios_rd08(bios, init->offset);
		trace("\t0x%02x\n", data[i]);
		init->offset++;
	पूर्ण

	अगर (init_exec(init)) अणु
		काष्ठा i2c_adapter *adap = init_i2c(init, index);
		काष्ठा i2c_msg msg = अणु
			.addr = addr, .flags = 0, .len = count, .buf = data,
		पूर्ण;
		पूर्णांक ret;

		अगर (adap && (ret = i2c_transfer(adap, &msg, 1)) != 1)
			warn("i2c wr failed, %d\n", ret);
	पूर्ण
पूर्ण

/**
 * INIT_TMDS - opcode 0x4f
 *
 */
अटल व्योम
init_पंचांगds(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 पंचांगds = nvbios_rd08(bios, init->offset + 1);
	u8 addr = nvbios_rd08(bios, init->offset + 2);
	u8 mask = nvbios_rd08(bios, init->offset + 3);
	u8 data = nvbios_rd08(bios, init->offset + 4);
	u32 reg = init_पंचांगds_reg(init, पंचांगds);

	trace("TMDS\tT[0x%02x][0x%02x] &= 0x%02x |= 0x%02x\n",
	      पंचांगds, addr, mask, data);
	init->offset += 5;

	अगर (reg == 0)
		वापस;

	init_wr32(init, reg + 0, addr | 0x00010000);
	init_wr32(init, reg + 4, data | (init_rd32(init, reg + 4) & mask));
	init_wr32(init, reg + 0, addr);
पूर्ण

/**
 * INIT_ZM_TMDS_GROUP - opcode 0x50
 *
 */
अटल व्योम
init_zm_पंचांगds_group(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8  पंचांगds = nvbios_rd08(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 2);
	u32  reg = init_पंचांगds_reg(init, पंचांगds);

	trace("TMDS_ZM_GROUP\tT[0x%02x]\n", पंचांगds);
	init->offset += 3;

	जबतक (count--) अणु
		u8 addr = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);

		trace("\t[0x%02x] = 0x%02x\n", addr, data);
		init->offset += 2;

		init_wr32(init, reg + 4, data);
		init_wr32(init, reg + 0, addr);
	पूर्ण
पूर्ण

/**
 * INIT_CR_INDEX_ADDRESS_LATCHED - opcode 0x51
 *
 */
अटल व्योम
init_cr_idx_adr_latch(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 addr0 = nvbios_rd08(bios, init->offset + 1);
	u8 addr1 = nvbios_rd08(bios, init->offset + 2);
	u8  base = nvbios_rd08(bios, init->offset + 3);
	u8 count = nvbios_rd08(bios, init->offset + 4);
	u8 save0;

	trace("CR_INDEX_ADDR C[%02x] C[%02x]\n", addr0, addr1);
	init->offset += 5;

	save0 = init_rdvgai(init, 0x03d4, addr0);
	जबतक (count--) अणु
		u8 data = nvbios_rd08(bios, init->offset);

		trace("\t\t[0x%02x] = 0x%02x\n", base, data);
		init->offset += 1;

		init_wrvgai(init, 0x03d4, addr0, base++);
		init_wrvgai(init, 0x03d4, addr1, data);
	पूर्ण
	init_wrvgai(init, 0x03d4, addr0, save0);
पूर्ण

/**
 * INIT_CR - opcode 0x52
 *
 */
अटल व्योम
init_cr(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 addr = nvbios_rd08(bios, init->offset + 1);
	u8 mask = nvbios_rd08(bios, init->offset + 2);
	u8 data = nvbios_rd08(bios, init->offset + 3);
	u8 val;

	trace("CR\t\tC[0x%02x] &= 0x%02x |= 0x%02x\n", addr, mask, data);
	init->offset += 4;

	val = init_rdvgai(init, 0x03d4, addr) & mask;
	init_wrvgai(init, 0x03d4, addr, val | data);
पूर्ण

/**
 * INIT_ZM_CR - opcode 0x53
 *
 */
अटल व्योम
init_zm_cr(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 addr = nvbios_rd08(bios, init->offset + 1);
	u8 data = nvbios_rd08(bios, init->offset + 2);

	trace("ZM_CR\tC[0x%02x] = 0x%02x\n", addr,  data);
	init->offset += 3;

	init_wrvgai(init, 0x03d4, addr, data);
पूर्ण

/**
 * INIT_ZM_CR_GROUP - opcode 0x54
 *
 */
अटल व्योम
init_zm_cr_group(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 count = nvbios_rd08(bios, init->offset + 1);

	trace("ZM_CR_GROUP\n");
	init->offset += 2;

	जबतक (count--) अणु
		u8 addr = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);

		trace("\t\tC[0x%02x] = 0x%02x\n", addr, data);
		init->offset += 2;

		init_wrvgai(init, 0x03d4, addr, data);
	पूर्ण
पूर्ण

/**
 * INIT_CONDITION_TIME - opcode 0x56
 *
 */
अटल व्योम
init_condition_समय(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8  cond = nvbios_rd08(bios, init->offset + 1);
	u8 retry = nvbios_rd08(bios, init->offset + 2);
	u8  रुको = min((u16)retry * 50, 100);

	trace("CONDITION_TIME\t0x%02x 0x%02x\n", cond, retry);
	init->offset += 3;

	अगर (!init_exec(init))
		वापस;

	जबतक (रुको--) अणु
		अगर (init_condition_met(init, cond))
			वापस;
		mdelay(20);
	पूर्ण

	init_exec_set(init, false);
पूर्ण

/**
 * INIT_LTIME - opcode 0x57
 *
 */
अटल व्योम
init_lसमय(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 msec = nvbios_rd16(bios, init->offset + 1);

	trace("LTIME\t0x%04x\n", msec);
	init->offset += 3;

	अगर (init_exec(init))
		mdelay(msec);
पूर्ण

/**
 * INIT_ZM_REG_SEQUENCE - opcode 0x58
 *
 */
अटल व्योम
init_zm_reg_sequence(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 base = nvbios_rd32(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 5);

	trace("ZM_REG_SEQUENCE\t0x%02x\n", count);
	init->offset += 6;

	जबतक (count--) अणु
		u32 data = nvbios_rd32(bios, init->offset);

		trace("\t\tR[0x%06x] = 0x%08x\n", base, data);
		init->offset += 4;

		init_wr32(init, base, data);
		base += 4;
	पूर्ण
पूर्ण

/**
 * INIT_PLL_INसूचीECT - opcode 0x59
 *
 */
अटल व्योम
init_pll_indirect(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u16 addr = nvbios_rd16(bios, init->offset + 5);
	u32 freq = (u32)nvbios_rd16(bios, addr) * 1000;

	trace("PLL_INDIRECT\tR[0x%06x] =PLL= VBIOS[%04x] = %dkHz\n",
	      reg, addr, freq);
	init->offset += 7;

	init_prog_pll(init, reg, freq);
पूर्ण

/**
 * INIT_ZM_REG_INसूचीECT - opcode 0x5a
 *
 */
अटल व्योम
init_zm_reg_indirect(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u16 addr = nvbios_rd16(bios, init->offset + 5);
	u32 data = nvbios_rd32(bios, addr);

	trace("ZM_REG_INDIRECT\tR[0x%06x] = VBIOS[0x%04x] = 0x%08x\n",
	      reg, addr, data);
	init->offset += 7;

	init_wr32(init, addr, data);
पूर्ण

/**
 * INIT_SUB_सूचीECT - opcode 0x5b
 *
 */
अटल व्योम
init_sub_direct(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 addr = nvbios_rd16(bios, init->offset + 1);
	u16 save;

	trace("SUB_DIRECT\t0x%04x\n", addr);

	अगर (init_exec(init)) अणु
		save = init->offset;
		init->offset = addr;
		अगर (nvbios_exec(init)) अणु
			error("error parsing sub-table\n");
			वापस;
		पूर्ण
		init->offset = save;
	पूर्ण

	init->offset += 3;
पूर्ण

/**
 * INIT_JUMP - opcode 0x5c
 *
 */
अटल व्योम
init_jump(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 offset = nvbios_rd16(bios, init->offset + 1);

	trace("JUMP\t0x%04x\n", offset);

	अगर (init_exec(init))
		init->offset = offset;
	अन्यथा
		init->offset += 3;
पूर्ण

/**
 * INIT_I2C_IF - opcode 0x5e
 *
 */
अटल व्योम
init_i2c_अगर(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2);
	u8   reg = nvbios_rd08(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8  data = nvbios_rd08(bios, init->offset + 5);
	u8 value;

	trace("I2C_IF\tI2C[0x%02x][0x%02x][0x%02x] & 0x%02x == 0x%02x\n",
	      index, addr, reg, mask, data);
	init->offset += 6;
	init_exec_क्रमce(init, true);

	value = init_rdi2cr(init, index, addr, reg);
	अगर ((value & mask) != data)
		init_exec_set(init, false);

	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_COPY_NV_REG - opcode 0x5f
 *
 */
अटल व्योम
init_copy_nv_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  sreg = nvbios_rd32(bios, init->offset + 1);
	u8  shअगरt = nvbios_rd08(bios, init->offset + 5);
	u32 smask = nvbios_rd32(bios, init->offset + 6);
	u32  sxor = nvbios_rd32(bios, init->offset + 10);
	u32  dreg = nvbios_rd32(bios, init->offset + 14);
	u32 dmask = nvbios_rd32(bios, init->offset + 18);
	u32 data;

	trace("COPY_NV_REG\tR[0x%06x] &= 0x%08x |= "
	      "((R[0x%06x] %s 0x%02x) & 0x%08x ^ 0x%08x)\न",
	      dreg, dmask, sreg, (shअगरt & 0x80) ? "<<" : ">>",
	      (shअगरt & 0x80) ? (0x100 - shअगरt) : shअगरt, smask, sxor);
	init->offset += 22;

	data = init_shअगरt(init_rd32(init, sreg), shअगरt);
	init_mask(init, dreg, ~dmask, (data & smask) ^ sxor);
पूर्ण

/**
 * INIT_ZM_INDEX_IO - opcode 0x62
 *
 */
अटल व्योम
init_zm_index_io(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd08(bios, init->offset + 3);
	u8  data = nvbios_rd08(bios, init->offset + 4);

	trace("ZM_INDEX_IO\tI[0x%04x][0x%02x] = 0x%02x\n", port, index, data);
	init->offset += 5;

	init_wrvgai(init, port, index, data);
पूर्ण

/**
 * INIT_COMPUTE_MEM - opcode 0x63
 *
 */
अटल व्योम
init_compute_mem(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_devinit *devinit = init->subdev->device->devinit;

	trace("COMPUTE_MEM\n");
	init->offset += 1;

	init_exec_क्रमce(init, true);
	अगर (init_exec(init))
		nvkm_devinit_meminit(devinit);
	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_RESET - opcode 0x65
 *
 */
अटल व्योम
init_reset(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32   reg = nvbios_rd32(bios, init->offset + 1);
	u32 data1 = nvbios_rd32(bios, init->offset + 5);
	u32 data2 = nvbios_rd32(bios, init->offset + 9);
	u32 savepci19;

	trace("RESET\tR[0x%08x] = 0x%08x, 0x%08x", reg, data1, data2);
	init->offset += 13;
	init_exec_क्रमce(init, true);

	savepci19 = init_mask(init, 0x00184c, 0x00000f00, 0x00000000);
	init_wr32(init, reg, data1);
	udelay(10);
	init_wr32(init, reg, data2);
	init_wr32(init, 0x00184c, savepci19);
	init_mask(init, 0x001850, 0x00000001, 0x00000000);

	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_CONFIGURE_MEM - opcode 0x66
 *
 */
अटल u16
init_configure_mem_clk(काष्ठा nvbios_init *init)
अणु
	u16 mdata = bmp_mem_init_table(init->subdev->device->bios);
	अगर (mdata)
		mdata += (init_rdvgai(init, 0x03d4, 0x3c) >> 4) * 66;
	वापस mdata;
पूर्ण

अटल व्योम
init_configure_mem(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 mdata, sdata;
	u32 addr, data;

	trace("CONFIGURE_MEM\n");
	init->offset += 1;

	अगर (bios->version.major > 2) अणु
		init_करोne(init);
		वापस;
	पूर्ण
	init_exec_क्रमce(init, true);

	mdata = init_configure_mem_clk(init);
	sdata = bmp_sdr_seq_table(bios);
	अगर (nvbios_rd08(bios, mdata) & 0x01)
		sdata = bmp_ddr_seq_table(bios);
	mdata += 6; /* skip to data */

	data = init_rdvgai(init, 0x03c4, 0x01);
	init_wrvgai(init, 0x03c4, 0x01, data | 0x20);

	क्रम (; (addr = nvbios_rd32(bios, sdata)) != 0xffffffff; sdata += 4) अणु
		चयन (addr) अणु
		हाल 0x10021c: /* CKE_NORMAL */
		हाल 0x1002d0: /* CMD_REFRESH */
		हाल 0x1002d4: /* CMD_PRECHARGE */
			data = 0x00000001;
			अवरोध;
		शेष:
			data = nvbios_rd32(bios, mdata);
			mdata += 4;
			अगर (data == 0xffffffff)
				जारी;
			अवरोध;
		पूर्ण

		init_wr32(init, addr, data);
	पूर्ण

	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_CONFIGURE_CLK - opcode 0x67
 *
 */
अटल व्योम
init_configure_clk(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 mdata, घड़ी;

	trace("CONFIGURE_CLK\n");
	init->offset += 1;

	अगर (bios->version.major > 2) अणु
		init_करोne(init);
		वापस;
	पूर्ण
	init_exec_क्रमce(init, true);

	mdata = init_configure_mem_clk(init);

	/* NVPLL */
	घड़ी = nvbios_rd16(bios, mdata + 4) * 10;
	init_prog_pll(init, 0x680500, घड़ी);

	/* MPLL */
	घड़ी = nvbios_rd16(bios, mdata + 2) * 10;
	अगर (nvbios_rd08(bios, mdata) & 0x01)
		घड़ी *= 2;
	init_prog_pll(init, 0x680504, घड़ी);

	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_CONFIGURE_PREINIT - opcode 0x68
 *
 */
अटल व्योम
init_configure_preinit(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 strap;

	trace("CONFIGURE_PREINIT\n");
	init->offset += 1;

	अगर (bios->version.major > 2) अणु
		init_करोne(init);
		वापस;
	पूर्ण
	init_exec_क्रमce(init, true);

	strap = init_rd32(init, 0x101000);
	strap = ((strap << 2) & 0xf0) | ((strap & 0x40) >> 6);
	init_wrvgai(init, 0x03d4, 0x3c, strap);

	init_exec_क्रमce(init, false);
पूर्ण

/**
 * INIT_IO - opcode 0x69
 *
 */
अटल व्योम
init_io(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8  mask = nvbios_rd16(bios, init->offset + 3);
	u8  data = nvbios_rd16(bios, init->offset + 4);
	u8 value;

	trace("IO\t\tI[0x%04x] &= 0x%02x |= 0x%02x\n", port, mask, data);
	init->offset += 5;

	/* ummm.. yes.. should really figure out wtf this is and why it's
	 * needed some day..  it's almost certainly wrong, but, it also
	 * somehow makes things work...
	 */
	अगर (bios->subdev.device->card_type >= NV_50 &&
	    port == 0x03c3 && data == 0x01) अणु
		init_mask(init, 0x614100, 0xf0800000, 0x00800000);
		init_mask(init, 0x00e18c, 0x00020000, 0x00020000);
		init_mask(init, 0x614900, 0xf0800000, 0x00800000);
		init_mask(init, 0x000200, 0x40000000, 0x00000000);
		mdelay(10);
		init_mask(init, 0x00e18c, 0x00020000, 0x00000000);
		init_mask(init, 0x000200, 0x40000000, 0x40000000);
		init_wr32(init, 0x614100, 0x00800018);
		init_wr32(init, 0x614900, 0x00800018);
		mdelay(10);
		init_wr32(init, 0x614100, 0x10000018);
		init_wr32(init, 0x614900, 0x10000018);
	पूर्ण

	value = init_rdport(init, port) & mask;
	init_wrport(init, port, data | value);
पूर्ण

/**
 * INIT_SUB - opcode 0x6b
 *
 */
अटल व्योम
init_sub(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u16 addr, save;

	trace("SUB\t0x%02x\n", index);

	addr = init_script(bios, index);
	अगर (addr && init_exec(init)) अणु
		save = init->offset;
		init->offset = addr;
		अगर (nvbios_exec(init)) अणु
			error("error parsing sub-table\n");
			वापस;
		पूर्ण
		init->offset = save;
	पूर्ण

	init->offset += 2;
पूर्ण

/**
 * INIT_RAM_CONDITION - opcode 0x6d
 *
 */
अटल व्योम
init_ram_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8  mask = nvbios_rd08(bios, init->offset + 1);
	u8 value = nvbios_rd08(bios, init->offset + 2);

	trace("RAM_CONDITION\t"
	      "(R[0x100000] & 0x%02x) == 0x%02x\n", mask, value);
	init->offset += 3;

	अगर ((init_rd32(init, 0x100000) & mask) != value)
		init_exec_set(init, false);
पूर्ण

/**
 * INIT_NV_REG - opcode 0x6e
 *
 */
अटल व्योम
init_nv_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u32 mask = nvbios_rd32(bios, init->offset + 5);
	u32 data = nvbios_rd32(bios, init->offset + 9);

	trace("NV_REG\tR[0x%06x] &= 0x%08x |= 0x%08x\n", reg, mask, data);
	init->offset += 13;

	init_mask(init, reg, ~mask, data);
पूर्ण

/**
 * INIT_MACRO - opcode 0x6f
 *
 */
अटल व्योम
init_macro(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8  macro = nvbios_rd08(bios, init->offset + 1);
	u16 table;

	trace("MACRO\t0x%02x\n", macro);

	table = init_macro_table(init);
	अगर (table) अणु
		u32 addr = nvbios_rd32(bios, table + (macro * 8) + 0);
		u32 data = nvbios_rd32(bios, table + (macro * 8) + 4);
		trace("\t\tR[0x%06x] = 0x%08x\n", addr, data);
		init_wr32(init, addr, data);
	पूर्ण

	init->offset += 2;
पूर्ण

/**
 * INIT_RESUME - opcode 0x72
 *
 */
अटल व्योम
init_resume(काष्ठा nvbios_init *init)
अणु
	trace("RESUME\n");
	init->offset += 1;
	init_exec_set(init, true);
पूर्ण

/**
 * INIT_STRAP_CONDITION - opcode 0x73
 *
 */
अटल व्योम
init_strap_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 mask = nvbios_rd32(bios, init->offset + 1);
	u32 value = nvbios_rd32(bios, init->offset + 5);

	trace("STRAP_CONDITION\t(R[0x101000] & 0x%08x) == 0x%08x\n", mask, value);
	init->offset += 9;

	अगर ((init_rd32(init, 0x101000) & mask) != value)
		init_exec_set(init, false);
पूर्ण

/**
 * INIT_TIME - opcode 0x74
 *
 */
अटल व्योम
init_समय(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 usec = nvbios_rd16(bios, init->offset + 1);

	trace("TIME\t0x%04x\n", usec);
	init->offset += 3;

	अगर (init_exec(init)) अणु
		अगर (usec < 1000)
			udelay(usec);
		अन्यथा
			mdelay((usec + 900) / 1000);
	पूर्ण
पूर्ण

/**
 * INIT_CONDITION - opcode 0x75
 *
 */
अटल व्योम
init_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_rd08(bios, init->offset + 1);

	trace("CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	अगर (!init_condition_met(init, cond))
		init_exec_set(init, false);
पूर्ण

/**
 * INIT_IO_CONDITION - opcode 0x76
 *
 */
अटल व्योम
init_io_condition(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 cond = nvbios_rd08(bios, init->offset + 1);

	trace("IO_CONDITION\t0x%02x\n", cond);
	init->offset += 2;

	अगर (!init_io_condition_met(init, cond))
		init_exec_set(init, false);
पूर्ण

/**
 * INIT_ZM_REG16 - opcode 0x77
 *
 */
अटल व्योम
init_zm_reg16(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u16 data = nvbios_rd16(bios, init->offset + 5);

	trace("ZM_REG\tR[0x%06x] = 0x%04x\n", addr, data);
	init->offset += 7;

	init_wr32(init, addr, data);
पूर्ण

/**
 * INIT_INDEX_IO - opcode 0x78
 *
 */
अटल व्योम
init_index_io(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u16 port = nvbios_rd16(bios, init->offset + 1);
	u8 index = nvbios_rd16(bios, init->offset + 3);
	u8  mask = nvbios_rd08(bios, init->offset + 4);
	u8  data = nvbios_rd08(bios, init->offset + 5);
	u8 value;

	trace("INDEX_IO\tI[0x%04x][0x%02x] &= 0x%02x |= 0x%02x\n",
	      port, index, mask, data);
	init->offset += 6;

	value = init_rdvgai(init, port, index) & mask;
	init_wrvgai(init, port, index, data | value);
पूर्ण

/**
 * INIT_PLL - opcode 0x79
 *
 */
अटल व्योम
init_pll(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32  reg = nvbios_rd32(bios, init->offset + 1);
	u32 freq = nvbios_rd16(bios, init->offset + 5) * 10;

	trace("PLL\tR[0x%06x] =PLL= %dkHz\n", reg, freq);
	init->offset += 7;

	init_prog_pll(init, reg, freq);
पूर्ण

/**
 * INIT_ZM_REG - opcode 0x7a
 *
 */
अटल व्योम
init_zm_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u32 data = nvbios_rd32(bios, init->offset + 5);

	trace("ZM_REG\tR[0x%06x] = 0x%08x\n", addr, data);
	init->offset += 9;

	अगर (addr == 0x000200)
		data |= 0x00000001;

	init_wr32(init, addr, data);
पूर्ण

/**
 * INIT_RAM_RESTRICT_PLL - opcde 0x87
 *
 */
अटल व्योम
init_ram_restrict_pll(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8  type = nvbios_rd08(bios, init->offset + 1);
	u8 count = init_ram_restrict_group_count(init);
	u8 strap = init_ram_restrict(init);
	u8 cconf;

	trace("RAM_RESTRICT_PLL\t0x%02x\n", type);
	init->offset += 2;

	क्रम (cconf = 0; cconf < count; cconf++) अणु
		u32 freq = nvbios_rd32(bios, init->offset);

		अगर (cconf == strap) अणु
			trace("%dkHz *\n", freq);
			init_prog_pll(init, type, freq);
		पूर्ण अन्यथा अणु
			trace("%dkHz\n", freq);
		पूर्ण

		init->offset += 4;
	पूर्ण
पूर्ण

/**
 * INIT_RESET_BEGUN - opcode 0x8c
 *
 */
अटल व्योम
init_reset_begun(काष्ठा nvbios_init *init)
अणु
	trace("RESET_BEGUN\n");
	init->offset += 1;
पूर्ण

/**
 * INIT_RESET_END - opcode 0x8d
 *
 */
अटल व्योम
init_reset_end(काष्ठा nvbios_init *init)
अणु
	trace("RESET_END\n");
	init->offset += 1;
पूर्ण

/**
 * INIT_GPIO - opcode 0x8e
 *
 */
अटल व्योम
init_gpio(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_gpio *gpio = init->subdev->device->gpio;

	trace("GPIO\n");
	init->offset += 1;

	अगर (init_exec(init))
		nvkm_gpio_reset(gpio, DCB_GPIO_UNUSED);
पूर्ण

/**
 * INIT_RAM_RESTRICT_ZM_GROUP - opcode 0x8f
 *
 */
अटल व्योम
init_ram_restrict_zm_reg_group(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u8  incr = nvbios_rd08(bios, init->offset + 5);
	u8   num = nvbios_rd08(bios, init->offset + 6);
	u8 count = init_ram_restrict_group_count(init);
	u8 index = init_ram_restrict(init);
	u8 i, j;

	trace("RAM_RESTRICT_ZM_REG_GROUP\t"
	      "R[0x%08x] 0x%02x 0x%02x\n", addr, incr, num);
	init->offset += 7;

	क्रम (i = 0; i < num; i++) अणु
		trace("\tR[0x%06x] = {\n", addr);
		क्रम (j = 0; j < count; j++) अणु
			u32 data = nvbios_rd32(bios, init->offset);

			अगर (j == index) अणु
				trace("\t\t0x%08x *\n", data);
				init_wr32(init, addr, data);
			पूर्ण अन्यथा अणु
				trace("\t\t0x%08x\n", data);
			पूर्ण

			init->offset += 4;
		पूर्ण
		trace("\t}\n");
		addr += incr;
	पूर्ण
पूर्ण

/**
 * INIT_COPY_ZM_REG - opcode 0x90
 *
 */
अटल व्योम
init_copy_zm_reg(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 sreg = nvbios_rd32(bios, init->offset + 1);
	u32 dreg = nvbios_rd32(bios, init->offset + 5);

	trace("COPY_ZM_REG\tR[0x%06x] = R[0x%06x]\n", dreg, sreg);
	init->offset += 9;

	init_wr32(init, dreg, init_rd32(init, sreg));
पूर्ण

/**
 * INIT_ZM_REG_GROUP - opcode 0x91
 *
 */
अटल व्योम
init_zm_reg_group(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 5);

	trace("ZM_REG_GROUP\tR[0x%06x] =\n", addr);
	init->offset += 6;

	जबतक (count--) अणु
		u32 data = nvbios_rd32(bios, init->offset);
		trace("\t0x%08x\n", data);
		init_wr32(init, addr, data);
		init->offset += 4;
	पूर्ण
पूर्ण

/**
 * INIT_XLAT - opcode 0x96
 *
 */
अटल व्योम
init_xlat(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 saddr = nvbios_rd32(bios, init->offset + 1);
	u8 sshअगरt = nvbios_rd08(bios, init->offset + 5);
	u8  smask = nvbios_rd08(bios, init->offset + 6);
	u8  index = nvbios_rd08(bios, init->offset + 7);
	u32 daddr = nvbios_rd32(bios, init->offset + 8);
	u32 dmask = nvbios_rd32(bios, init->offset + 12);
	u8  shअगरt = nvbios_rd08(bios, init->offset + 16);
	u32 data;

	trace("INIT_XLAT\tR[0x%06x] &= 0x%08x |= "
	      "(X%02x((R[0x%06x] %s 0x%02x) & 0x%02x) << 0x%02x)\n",
	      daddr, dmask, index, saddr, (sshअगरt & 0x80) ? "<<" : ">>",
	      (sshअगरt & 0x80) ? (0x100 - sshअगरt) : sshअगरt, smask, shअगरt);
	init->offset += 17;

	data = init_shअगरt(init_rd32(init, saddr), sshअगरt) & smask;
	data = init_xlat_(init, index, data) << shअगरt;
	init_mask(init, daddr, ~dmask, data);
पूर्ण

/**
 * INIT_ZM_MASK_ADD - opcode 0x97
 *
 */
अटल व्योम
init_zm_mask_add(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u32 mask = nvbios_rd32(bios, init->offset + 5);
	u32  add = nvbios_rd32(bios, init->offset + 9);
	u32 data;

	trace("ZM_MASK_ADD\tR[0x%06x] &= 0x%08x += 0x%08x\n", addr, mask, add);
	init->offset += 13;

	data =  init_rd32(init, addr);
	data = (data & mask) | ((data + add) & ~mask);
	init_wr32(init, addr, data);
पूर्ण

/**
 * INIT_AUXCH - opcode 0x98
 *
 */
अटल व्योम
init_auxch(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 5);

	trace("AUXCH\tAUX[0x%08x] 0x%02x\n", addr, count);
	init->offset += 6;

	जबतक (count--) अणु
		u8 mask = nvbios_rd08(bios, init->offset + 0);
		u8 data = nvbios_rd08(bios, init->offset + 1);
		trace("\tAUX[0x%08x] &= 0x%02x |= 0x%02x\n", addr, mask, data);
		mask = init_rdauxr(init, addr) & mask;
		init_wrauxr(init, addr, mask | data);
		init->offset += 2;
	पूर्ण
पूर्ण

/**
 * INIT_AUXCH - opcode 0x99
 *
 */
अटल व्योम
init_zm_auxch(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u32 addr = nvbios_rd32(bios, init->offset + 1);
	u8 count = nvbios_rd08(bios, init->offset + 5);

	trace("ZM_AUXCH\tAUX[0x%08x] 0x%02x\n", addr, count);
	init->offset += 6;

	जबतक (count--) अणु
		u8 data = nvbios_rd08(bios, init->offset + 0);
		trace("\tAUX[0x%08x] = 0x%02x\n", addr, data);
		init_wrauxr(init, addr, data);
		init->offset += 1;
	पूर्ण
पूर्ण

/**
 * INIT_I2C_LONG_IF - opcode 0x9a
 *
 */
अटल व्योम
init_i2c_दीर्घ_अगर(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	u8 index = nvbios_rd08(bios, init->offset + 1);
	u8  addr = nvbios_rd08(bios, init->offset + 2) >> 1;
	u8 reglo = nvbios_rd08(bios, init->offset + 3);
	u8 reghi = nvbios_rd08(bios, init->offset + 4);
	u8  mask = nvbios_rd08(bios, init->offset + 5);
	u8  data = nvbios_rd08(bios, init->offset + 6);
	काष्ठा i2c_adapter *adap;

	trace("I2C_LONG_IF\t"
	      "I2C[0x%02x][0x%02x][0x%02x%02x] & 0x%02x == 0x%02x\n",
	      index, addr, reglo, reghi, mask, data);
	init->offset += 7;

	adap = init_i2c(init, index);
	अगर (adap) अणु
		u8 i[2] = अणु reghi, reglo पूर्ण;
		u8 o[1] = अणुपूर्ण;
		काष्ठा i2c_msg msg[] = अणु
			अणु .addr = addr, .flags = 0, .len = 2, .buf = i पूर्ण,
			अणु .addr = addr, .flags = I2C_M_RD, .len = 1, .buf = o पूर्ण
		पूर्ण;
		पूर्णांक ret;

		ret = i2c_transfer(adap, msg, 2);
		अगर (ret == 2 && ((o[0] & mask) == data))
			वापस;
	पूर्ण

	init_exec_set(init, false);
पूर्ण

/**
 * INIT_GPIO_NE - opcode 0xa9
 *
 */
अटल व्योम
init_gpio_ne(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;
	काष्ठा nvkm_gpio *gpio = bios->subdev.device->gpio;
	काष्ठा dcb_gpio_func func;
	u8 count = nvbios_rd08(bios, init->offset + 1);
	u8 idx = 0, ver, len;
	u16 data, i;

	trace("GPIO_NE\t");
	init->offset += 2;

	क्रम (i = init->offset; i < init->offset + count; i++)
		cont("0x%02x ", nvbios_rd08(bios, i));
	cont("\n");

	जबतक ((data = dcb_gpio_parse(bios, 0, idx++, &ver, &len, &func))) अणु
		अगर (func.func != DCB_GPIO_UNUSED) अणु
			क्रम (i = init->offset; i < init->offset + count; i++) अणु
				अगर (func.func == nvbios_rd08(bios, i))
					अवरोध;
			पूर्ण

			trace("\tFUNC[0x%02x]", func.func);
			अगर (i == (init->offset + count)) अणु
				cont(" *");
				अगर (init_exec(init))
					nvkm_gpio_reset(gpio, func.func);
			पूर्ण
			cont("\n");
		पूर्ण
	पूर्ण

	init->offset += count;
पूर्ण

अटल काष्ठा nvbios_init_opcode अणु
	व्योम (*exec)(काष्ठा nvbios_init *);
पूर्ण init_opcode[] = अणु
	[0x32] = अणु init_io_restrict_prog पूर्ण,
	[0x33] = अणु init_repeat पूर्ण,
	[0x34] = अणु init_io_restrict_pll पूर्ण,
	[0x36] = अणु init_end_repeat पूर्ण,
	[0x37] = अणु init_copy पूर्ण,
	[0x38] = अणु init_not पूर्ण,
	[0x39] = अणु init_io_flag_condition पूर्ण,
	[0x3a] = अणु init_generic_condition पूर्ण,
	[0x3b] = अणु init_io_mask_or पूर्ण,
	[0x3c] = अणु init_io_or पूर्ण,
	[0x47] = अणु init_andn_reg पूर्ण,
	[0x48] = अणु init_or_reg पूर्ण,
	[0x49] = अणु init_idx_addr_latched पूर्ण,
	[0x4a] = अणु init_io_restrict_pll2 पूर्ण,
	[0x4b] = अणु init_pll2 पूर्ण,
	[0x4c] = अणु init_i2c_byte पूर्ण,
	[0x4d] = अणु init_zm_i2c_byte पूर्ण,
	[0x4e] = अणु init_zm_i2c पूर्ण,
	[0x4f] = अणु init_पंचांगds पूर्ण,
	[0x50] = अणु init_zm_पंचांगds_group पूर्ण,
	[0x51] = अणु init_cr_idx_adr_latch पूर्ण,
	[0x52] = अणु init_cr पूर्ण,
	[0x53] = अणु init_zm_cr पूर्ण,
	[0x54] = अणु init_zm_cr_group पूर्ण,
	[0x56] = अणु init_condition_समय पूर्ण,
	[0x57] = अणु init_lसमय पूर्ण,
	[0x58] = अणु init_zm_reg_sequence पूर्ण,
	[0x59] = अणु init_pll_indirect पूर्ण,
	[0x5a] = अणु init_zm_reg_indirect पूर्ण,
	[0x5b] = अणु init_sub_direct पूर्ण,
	[0x5c] = अणु init_jump पूर्ण,
	[0x5e] = अणु init_i2c_अगर पूर्ण,
	[0x5f] = अणु init_copy_nv_reg पूर्ण,
	[0x62] = अणु init_zm_index_io पूर्ण,
	[0x63] = अणु init_compute_mem पूर्ण,
	[0x65] = अणु init_reset पूर्ण,
	[0x66] = अणु init_configure_mem पूर्ण,
	[0x67] = अणु init_configure_clk पूर्ण,
	[0x68] = अणु init_configure_preinit पूर्ण,
	[0x69] = अणु init_io पूर्ण,
	[0x6b] = अणु init_sub पूर्ण,
	[0x6d] = अणु init_ram_condition पूर्ण,
	[0x6e] = अणु init_nv_reg पूर्ण,
	[0x6f] = अणु init_macro पूर्ण,
	[0x71] = अणु init_करोne पूर्ण,
	[0x72] = अणु init_resume पूर्ण,
	[0x73] = अणु init_strap_condition पूर्ण,
	[0x74] = अणु init_समय पूर्ण,
	[0x75] = अणु init_condition पूर्ण,
	[0x76] = अणु init_io_condition पूर्ण,
	[0x77] = अणु init_zm_reg16 पूर्ण,
	[0x78] = अणु init_index_io पूर्ण,
	[0x79] = अणु init_pll पूर्ण,
	[0x7a] = अणु init_zm_reg पूर्ण,
	[0x87] = अणु init_ram_restrict_pll पूर्ण,
	[0x8c] = अणु init_reset_begun पूर्ण,
	[0x8d] = अणु init_reset_end पूर्ण,
	[0x8e] = अणु init_gpio पूर्ण,
	[0x8f] = अणु init_ram_restrict_zm_reg_group पूर्ण,
	[0x90] = अणु init_copy_zm_reg पूर्ण,
	[0x91] = अणु init_zm_reg_group पूर्ण,
	[0x92] = अणु init_reserved पूर्ण,
	[0x96] = अणु init_xlat पूर्ण,
	[0x97] = अणु init_zm_mask_add पूर्ण,
	[0x98] = अणु init_auxch पूर्ण,
	[0x99] = अणु init_zm_auxch पूर्ण,
	[0x9a] = अणु init_i2c_दीर्घ_अगर पूर्ण,
	[0xa9] = अणु init_gpio_ne पूर्ण,
	[0xaa] = अणु init_reserved पूर्ण,
पूर्ण;

पूर्णांक
nvbios_exec(काष्ठा nvbios_init *init)
अणु
	काष्ठा nvkm_bios *bios = init->subdev->device->bios;

	init->nested++;
	जबतक (init->offset) अणु
		u8 opcode = nvbios_rd08(bios, init->offset);
		अगर (opcode >= ARRAY_SIZE(init_opcode) ||
		    !init_opcode[opcode].exec) अणु
			error("unknown opcode 0x%02x\n", opcode);
			वापस -EINVAL;
		पूर्ण

		init_opcode[opcode].exec(init);
	पूर्ण
	init->nested--;
	वापस 0;
पूर्ण

पूर्णांक
nvbios_post(काष्ठा nvkm_subdev *subdev, bool execute)
अणु
	काष्ठा nvkm_bios *bios = subdev->device->bios;
	पूर्णांक ret = 0;
	पूर्णांक i = -1;
	u16 data;

	अगर (execute)
		nvkm_debug(subdev, "running init tables\n");
	जबतक (!ret && (data = (init_script(bios, ++i)))) अणु
		ret = nvbios_init(subdev, data,
			init.execute = execute ? 1 : 0;
		      );
	पूर्ण

	/* the vbios parser will run this right after the normal init
	 * tables, whereas the binary driver appears to run it later.
	 */
	अगर (!ret && (data = init_unknown_script(bios))) अणु
		ret = nvbios_init(subdev, data,
			init.execute = execute ? 1 : 0;
		      );
	पूर्ण

	वापस ret;
पूर्ण
