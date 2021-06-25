<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * cx88-vp3054-i2c.h  --  support क्रम the secondary I2C bus of the
 *			  DNTV Live! DVB-T Pro (VP-3054), wired as:
 *			  GPIO[0] -> SCL, GPIO[1] -> SDA
 *
 * (c) 2005 Chris Pascoe <c.pascoe@itee.uq.edu.au>
 */

/* ----------------------------------------------------------------------- */
काष्ठा vp3054_i2c_state अणु
	काष्ठा i2c_adapter         adap;
	काष्ठा i2c_algo_bit_data   algo;
	u32                        state;
पूर्ण;

/* ----------------------------------------------------------------------- */
#अगर IS_ENABLED(CONFIG_VIDEO_CX88_VP3054)
पूर्णांक  vp3054_i2c_probe(काष्ठा cx8802_dev *dev);
व्योम vp3054_i2c_हटाओ(काष्ठा cx8802_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक  vp3054_i2c_probe(काष्ठा cx8802_dev *dev)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम vp3054_i2c_हटाओ(काष्ठा cx8802_dev *dev)
अणु पूर्ण
#पूर्ण_अगर
