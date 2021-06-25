<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVKM_I2C_H__
#घोषणा __NVKM_I2C_H__
#समावेश <core/subdev.h>
#समावेश <core/event.h>

#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/i2c.h>

काष्ठा nvkm_i2c_ntfy_req अणु
#घोषणा NVKM_I2C_PLUG                                                      0x01
#घोषणा NVKM_I2C_UNPLUG                                                    0x02
#घोषणा NVKM_I2C_IRQ                                                       0x04
#घोषणा NVKM_I2C_DONE                                                      0x08
#घोषणा NVKM_I2C_ANY                                                       0x0f
	u8 mask;
	u8 port;
पूर्ण;

काष्ठा nvkm_i2c_ntfy_rep अणु
	u8 mask;
पूर्ण;

काष्ठा nvkm_i2c_bus_probe अणु
	काष्ठा i2c_board_info dev;
	u8 udelay; /* set to 0 to use the standard delay */
पूर्ण;

काष्ठा nvkm_i2c_bus अणु
	स्थिर काष्ठा nvkm_i2c_bus_func *func;
	काष्ठा nvkm_i2c_pad *pad;
#घोषणा NVKM_I2C_BUS_CCB(n) /* 'n' is ccb index */                           (n)
#घोषणा NVKM_I2C_BUS_EXT(n) /* 'n' is dcb बाह्यal encoder type */ ((n) + 0x100)
#घोषणा NVKM_I2C_BUS_PRI /* ccb primary comm. port */                        -1
#घोषणा NVKM_I2C_BUS_SEC /* ccb secondary comm. port */                      -2
	पूर्णांक id;

	काष्ठा mutex mutex;
	काष्ठा list_head head;
	काष्ठा i2c_adapter i2c;
	u8 enabled;
पूर्ण;

पूर्णांक nvkm_i2c_bus_acquire(काष्ठा nvkm_i2c_bus *);
व्योम nvkm_i2c_bus_release(काष्ठा nvkm_i2c_bus *);
पूर्णांक nvkm_i2c_bus_probe(काष्ठा nvkm_i2c_bus *, स्थिर अक्षर *,
		       काष्ठा nvkm_i2c_bus_probe *,
		       bool (*)(काष्ठा nvkm_i2c_bus *,
			        काष्ठा i2c_board_info *, व्योम *), व्योम *);

काष्ठा nvkm_i2c_aux अणु
	स्थिर काष्ठा nvkm_i2c_aux_func *func;
	काष्ठा nvkm_i2c_pad *pad;
#घोषणा NVKM_I2C_AUX_CCB(n) /* 'n' is ccb index */                           (n)
#घोषणा NVKM_I2C_AUX_EXT(n) /* 'n' is dcb बाह्यal encoder type */ ((n) + 0x100)
	पूर्णांक id;

	काष्ठा mutex mutex;
	काष्ठा list_head head;
	काष्ठा i2c_adapter i2c;
	u8 enabled;

	u32 पूर्णांकr;
पूर्ण;

व्योम nvkm_i2c_aux_monitor(काष्ठा nvkm_i2c_aux *, bool monitor);
पूर्णांक nvkm_i2c_aux_acquire(काष्ठा nvkm_i2c_aux *);
व्योम nvkm_i2c_aux_release(काष्ठा nvkm_i2c_aux *);
पूर्णांक nvkm_i2c_aux_xfer(काष्ठा nvkm_i2c_aux *, bool retry, u8 type,
		      u32 addr, u8 *data, u8 *size);
पूर्णांक nvkm_i2c_aux_lnk_ctl(काष्ठा nvkm_i2c_aux *, पूर्णांक link_nr, पूर्णांक link_bw,
			 bool enhanced_framing);

काष्ठा nvkm_i2c अणु
	स्थिर काष्ठा nvkm_i2c_func *func;
	काष्ठा nvkm_subdev subdev;

	काष्ठा list_head pad;
	काष्ठा list_head bus;
	काष्ठा list_head aux;

	काष्ठा nvkm_event event;
पूर्ण;

काष्ठा nvkm_i2c_bus *nvkm_i2c_bus_find(काष्ठा nvkm_i2c *, पूर्णांक);
काष्ठा nvkm_i2c_aux *nvkm_i2c_aux_find(काष्ठा nvkm_i2c *, पूर्णांक);

पूर्णांक nv04_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक nv4e_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक nv50_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक g94_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक gf117_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक gf119_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक gk104_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक gk110_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);
पूर्णांक gm200_i2c_new(काष्ठा nvkm_device *, क्रमागत nvkm_subdev_type, पूर्णांक inst, काष्ठा nvkm_i2c **);

अटल अंतरभूत पूर्णांक
nvkm_rdi2cr(काष्ठा i2c_adapter *adap, u8 addr, u8 reg)
अणु
	u8 val;
	काष्ठा i2c_msg msgs[] = अणु
		अणु .addr = addr, .flags = 0, .len = 1, .buf = &reg पूर्ण,
		अणु .addr = addr, .flags = I2C_M_RD, .len = 1, .buf = &val पूर्ण,
	पूर्ण;

	पूर्णांक ret = i2c_transfer(adap, msgs, ARRAY_SIZE(msgs));
	अगर (ret != 2)
		वापस -EIO;

	वापस val;
पूर्ण

अटल अंतरभूत पूर्णांक
nv_rd16i2cr(काष्ठा i2c_adapter *adap, u8 addr, u8 reg)
अणु
	u8 val[2];
	काष्ठा i2c_msg msgs[] = अणु
		अणु .addr = addr, .flags = 0, .len = 1, .buf = &reg पूर्ण,
		अणु .addr = addr, .flags = I2C_M_RD, .len = 2, .buf = val पूर्ण,
	पूर्ण;

	पूर्णांक ret = i2c_transfer(adap, msgs, ARRAY_SIZE(msgs));
	अगर (ret != 2)
		वापस -EIO;

	वापस val[0] << 8 | val[1];
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_wri2cr(काष्ठा i2c_adapter *adap, u8 addr, u8 reg, u8 val)
अणु
	u8 buf[2] = अणु reg, val पूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु .addr = addr, .flags = 0, .len = 2, .buf = buf पूर्ण,
	पूर्ण;

	पूर्णांक ret = i2c_transfer(adap, msgs, ARRAY_SIZE(msgs));
	अगर (ret != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nv_wr16i2cr(काष्ठा i2c_adapter *adap, u8 addr, u8 reg, u16 val)
अणु
	u8 buf[3] = अणु reg, val >> 8, val & 0xffपूर्ण;
	काष्ठा i2c_msg msgs[] = अणु
		अणु .addr = addr, .flags = 0, .len = 3, .buf = buf पूर्ण,
	पूर्ण;

	पूर्णांक ret = i2c_transfer(adap, msgs, ARRAY_SIZE(msgs));
	अगर (ret != 1)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल अंतरभूत bool
nvkm_probe_i2c(काष्ठा i2c_adapter *adap, u8 addr)
अणु
	वापस nvkm_rdi2cr(adap, addr, 0) >= 0;
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_rdaux(काष्ठा nvkm_i2c_aux *aux, u32 addr, u8 *data, u8 size)
अणु
	स्थिर u8 xfer = size;
	पूर्णांक ret = nvkm_i2c_aux_acquire(aux);
	अगर (ret == 0) अणु
		ret = nvkm_i2c_aux_xfer(aux, true, 9, addr, data, &size);
		WARN_ON(!ret && size != xfer);
		nvkm_i2c_aux_release(aux);
	पूर्ण
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
nvkm_wraux(काष्ठा nvkm_i2c_aux *aux, u32 addr, u8 *data, u8 size)
अणु
	पूर्णांक ret = nvkm_i2c_aux_acquire(aux);
	अगर (ret == 0) अणु
		ret = nvkm_i2c_aux_xfer(aux, true, 8, addr, data, &size);
		nvkm_i2c_aux_release(aux);
	पूर्ण
	वापस ret;
पूर्ण
#पूर्ण_अगर
