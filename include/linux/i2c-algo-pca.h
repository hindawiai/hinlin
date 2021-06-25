<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_I2C_ALGO_PCA_H
#घोषणा _LINUX_I2C_ALGO_PCA_H

/* Chips known to the pca algo */
#घोषणा I2C_PCA_CHIP_9564	0x00
#घोषणा I2C_PCA_CHIP_9665	0x01

/* Internal period क्रम PCA9665 oscilator */
#घोषणा I2C_PCA_OSC_PER		3 /* e10-8s */

/* Clock speeds क्रम the bus क्रम PCA9564*/
#घोषणा I2C_PCA_CON_330kHz	0x00
#घोषणा I2C_PCA_CON_288kHz	0x01
#घोषणा I2C_PCA_CON_217kHz	0x02
#घोषणा I2C_PCA_CON_146kHz	0x03
#घोषणा I2C_PCA_CON_88kHz	0x04
#घोषणा I2C_PCA_CON_59kHz	0x05
#घोषणा I2C_PCA_CON_44kHz	0x06
#घोषणा I2C_PCA_CON_36kHz	0x07

/* PCA9564 रेजिस्टरs */
#घोषणा I2C_PCA_STA		0x00 /* STATUS  Read Only  */
#घोषणा I2C_PCA_TO		0x00 /* TIMEOUT Write Only */
#घोषणा I2C_PCA_DAT		0x01 /* DATA    Read/Write */
#घोषणा I2C_PCA_ADR		0x02 /* OWN ADR Read/Write */
#घोषणा I2C_PCA_CON		0x03 /* CONTROL Read/Write */

/* PCA9665 रेजिस्टरs */
#घोषणा I2C_PCA_INDPTR          0x00 /* INसूचीECT Poपूर्णांकer Write Only */
#घोषणा I2C_PCA_IND             0x02 /* INसूचीECT Read/Write */

/* PCA9665 indirect रेजिस्टरs */
#घोषणा I2C_PCA_ICOUNT          0x00 /* Byte Count क्रम buffered mode */
#घोषणा I2C_PCA_IADR            0x01 /* OWN ADR */
#घोषणा I2C_PCA_ISCLL           0x02 /* SCL LOW period */
#घोषणा I2C_PCA_ISCLH           0x03 /* SCL HIGH period */
#घोषणा I2C_PCA_ITO             0x04 /* TIMEOUT */
#घोषणा I2C_PCA_IPRESET         0x05 /* Parallel bus reset */
#घोषणा I2C_PCA_IMODE           0x06 /* I2C Bus mode */

/* PCA9665 I2C bus mode */
#घोषणा I2C_PCA_MODE_STD        0x00 /* Standard mode */
#घोषणा I2C_PCA_MODE_FAST       0x01 /* Fast mode */
#घोषणा I2C_PCA_MODE_FASTP      0x02 /* Fast Plus mode */
#घोषणा I2C_PCA_MODE_TURBO      0x03 /* Turbo mode */


#घोषणा I2C_PCA_CON_AA		0x80 /* Assert Acknowledge */
#घोषणा I2C_PCA_CON_ENSIO	0x40 /* Enable */
#घोषणा I2C_PCA_CON_STA		0x20 /* Start */
#घोषणा I2C_PCA_CON_STO		0x10 /* Stop */
#घोषणा I2C_PCA_CON_SI		0x08 /* Serial Interrupt */
#घोषणा I2C_PCA_CON_CR		0x07 /* Clock Rate (MASK) */

/**
 * काष्ठा pca_i2c_bus_settings - The configured PCA i2c bus settings
 * @mode: Configured i2c bus mode
 * @tlow: Configured SCL LOW period
 * @thi: Configured SCL HIGH period
 * @घड़ी_freq: The configured घड़ी frequency
 */
काष्ठा pca_i2c_bus_settings अणु
	पूर्णांक mode;
	पूर्णांक tlow;
	पूर्णांक thi;
	पूर्णांक घड़ी_freq;
पूर्ण;

काष्ठा i2c_algo_pca_data अणु
	व्योम 				*data;	/* निजी low level data */
	व्योम (*ग_लिखो_byte)		(व्योम *data, पूर्णांक reg, पूर्णांक val);
	पूर्णांक  (*पढ़ो_byte)		(व्योम *data, पूर्णांक reg);
	पूर्णांक  (*रुको_क्रम_completion)	(व्योम *data);
	व्योम (*reset_chip)		(व्योम *data);
	/* For PCA9564, use one of the predefined frequencies:
	 * 330000, 288000, 217000, 146000, 88000, 59000, 44000, 36000
	 * For PCA9665, use the frequency you want here. */
	अचिन्हित पूर्णांक			i2c_घड़ी;
	अचिन्हित पूर्णांक			chip;
	काष्ठा pca_i2c_bus_settings		bus_settings;
पूर्ण;

पूर्णांक i2c_pca_add_bus(काष्ठा i2c_adapter *);
पूर्णांक i2c_pca_add_numbered_bus(काष्ठा i2c_adapter *);

#पूर्ण_अगर /* _LINUX_I2C_ALGO_PCA_H */
