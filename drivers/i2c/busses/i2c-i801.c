<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 1998 - 2002  Froकरो Looijaard <froकरोl@dds.nl>,
    Philip Edelbrock <phil@netroedge.com>, and Mark D. Studebaker
    <mdsxyz123@yahoo.com>
    Copyright (C) 2007 - 2014  Jean Delvare <jdelvare@suse.de>
    Copyright (C) 2010         Intel Corporation,
                               David Woodhouse <dwmw2@infradead.org>

*/

/*
 * Supports the following Intel I/O Controller Hubs (ICH):
 *
 *					I/O			Block	I2C
 *					region	SMBus	Block	proc.	block
 * Chip name			PCI ID	size	PEC	buffer	call	पढ़ो
 * ---------------------------------------------------------------------------
 * 82801AA (ICH)		0x2413	16	no	no	no	no
 * 82801AB (ICH0)		0x2423	16	no	no	no	no
 * 82801BA (ICH2)		0x2443	16	no	no	no	no
 * 82801CA (ICH3)		0x2483	32	soft	no	no	no
 * 82801DB (ICH4)		0x24c3	32	hard	yes	no	no
 * 82801E (ICH5)		0x24d3	32	hard	yes	yes	yes
 * 6300ESB			0x25a4	32	hard	yes	yes	yes
 * 82801F (ICH6)		0x266a	32	hard	yes	yes	yes
 * 6310ESB/6320ESB		0x269b	32	hard	yes	yes	yes
 * 82801G (ICH7)		0x27da	32	hard	yes	yes	yes
 * 82801H (ICH8)		0x283e	32	hard	yes	yes	yes
 * 82801I (ICH9)		0x2930	32	hard	yes	yes	yes
 * EP80579 (Tolapai)		0x5032	32	hard	yes	yes	yes
 * ICH10			0x3a30	32	hard	yes	yes	yes
 * ICH10			0x3a60	32	hard	yes	yes	yes
 * 5/3400 Series (PCH)		0x3b30	32	hard	yes	yes	yes
 * 6 Series (PCH)		0x1c22	32	hard	yes	yes	yes
 * Patsburg (PCH)		0x1d22	32	hard	yes	yes	yes
 * Patsburg (PCH) IDF		0x1d70	32	hard	yes	yes	yes
 * Patsburg (PCH) IDF		0x1d71	32	hard	yes	yes	yes
 * Patsburg (PCH) IDF		0x1d72	32	hard	yes	yes	yes
 * DH89xxCC (PCH)		0x2330	32	hard	yes	yes	yes
 * Panther Poपूर्णांक (PCH)		0x1e22	32	hard	yes	yes	yes
 * Lynx Poपूर्णांक (PCH)		0x8c22	32	hard	yes	yes	yes
 * Lynx Poपूर्णांक-LP (PCH)		0x9c22	32	hard	yes	yes	yes
 * Avoton (SOC)			0x1f3c	32	hard	yes	yes	yes
 * Wellsburg (PCH)		0x8d22	32	hard	yes	yes	yes
 * Wellsburg (PCH) MS		0x8d7d	32	hard	yes	yes	yes
 * Wellsburg (PCH) MS		0x8d7e	32	hard	yes	yes	yes
 * Wellsburg (PCH) MS		0x8d7f	32	hard	yes	yes	yes
 * Coleto Creek (PCH)		0x23b0	32	hard	yes	yes	yes
 * Wildcat Poपूर्णांक (PCH)		0x8ca2	32	hard	yes	yes	yes
 * Wildcat Poपूर्णांक-LP (PCH)	0x9ca2	32	hard	yes	yes	yes
 * BayTrail (SOC)		0x0f12	32	hard	yes	yes	yes
 * Braswell (SOC)		0x2292	32	hard	yes	yes	yes
 * Sunrise Poपूर्णांक-H (PCH) 	0xa123  32	hard	yes	yes	yes
 * Sunrise Poपूर्णांक-LP (PCH)	0x9d23	32	hard	yes	yes	yes
 * DNV (SOC)			0x19df	32	hard	yes	yes	yes
 * Emmitsburg (PCH)		0x1bc9	32	hard	yes	yes	yes
 * Broxton (SOC)		0x5ad4	32	hard	yes	yes	yes
 * Lewisburg (PCH)		0xa1a3	32	hard	yes	yes	yes
 * Lewisburg Supersku (PCH)	0xa223	32	hard	yes	yes	yes
 * Kaby Lake PCH-H (PCH)	0xa2a3	32	hard	yes	yes	yes
 * Gemini Lake (SOC)		0x31d4	32	hard	yes	yes	yes
 * Cannon Lake-H (PCH)		0xa323	32	hard	yes	yes	yes
 * Cannon Lake-LP (PCH)		0x9da3	32	hard	yes	yes	yes
 * Cedar Fork (PCH)		0x18df	32	hard	yes	yes	yes
 * Ice Lake-LP (PCH)		0x34a3	32	hard	yes	yes	yes
 * Comet Lake (PCH)		0x02a3	32	hard	yes	yes	yes
 * Comet Lake-H (PCH)		0x06a3	32	hard	yes	yes	yes
 * Elkhart Lake (PCH)		0x4b23	32	hard	yes	yes	yes
 * Tiger Lake-LP (PCH)		0xa0a3	32	hard	yes	yes	yes
 * Tiger Lake-H (PCH)		0x43a3	32	hard	yes	yes	yes
 * Jasper Lake (SOC)		0x4da3	32	hard	yes	yes	yes
 * Comet Lake-V (PCH)		0xa3a3	32	hard	yes	yes	yes
 * Alder Lake-S (PCH)		0x7aa3	32	hard	yes	yes	yes
 * Alder Lake-P (PCH)		0x51a3	32	hard	yes	yes	yes
 * Alder Lake-M (PCH)		0x54a3	32	hard	yes	yes	yes
 *
 * Features supported by this driver:
 * Software PEC				no
 * Hardware PEC				yes
 * Block buffer				yes
 * Block process call transaction	yes
 * I2C block पढ़ो transaction		yes (करोesn't use the block buffer)
 * Slave mode				no
 * SMBus Host Notअगरy			yes
 * Interrupt processing			yes
 *
 * See the file Documentation/i2c/busses/i2c-i801.rst क्रम details.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/रुको.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/itco_wdt.h>
#समावेश <linux/pm_runसमय.स>

#अगर IS_ENABLED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
#समावेश <linux/gpio/machine.h>
#समावेश <linux/platक्रमm_data/i2c-mux-gpपन.स>
#पूर्ण_अगर

/* I801 SMBus address offsets */
#घोषणा SMBHSTSTS(p)	(0 + (p)->smba)
#घोषणा SMBHSTCNT(p)	(2 + (p)->smba)
#घोषणा SMBHSTCMD(p)	(3 + (p)->smba)
#घोषणा SMBHSTADD(p)	(4 + (p)->smba)
#घोषणा SMBHSTDAT0(p)	(5 + (p)->smba)
#घोषणा SMBHSTDAT1(p)	(6 + (p)->smba)
#घोषणा SMBBLKDAT(p)	(7 + (p)->smba)
#घोषणा SMBPEC(p)	(8 + (p)->smba)		/* ICH3 and later */
#घोषणा SMBAUXSTS(p)	(12 + (p)->smba)	/* ICH4 and later */
#घोषणा SMBAUXCTL(p)	(13 + (p)->smba)	/* ICH4 and later */
#घोषणा SMBSLVSTS(p)	(16 + (p)->smba)	/* ICH3 and later */
#घोषणा SMBSLVCMD(p)	(17 + (p)->smba)	/* ICH3 and later */
#घोषणा SMBNTFDADD(p)	(20 + (p)->smba)	/* ICH3 and later */

/* PCI Address Constants */
#घोषणा SMBBAR		4
#घोषणा SMBPCICTL	0x004
#घोषणा SMBPCISTS	0x006
#घोषणा SMBHSTCFG	0x040
#घोषणा TCOBASE		0x050
#घोषणा TCOCTL		0x054

#घोषणा SBREG_BAR		0x10
#घोषणा SBREG_SMBCTRL		0xc6000c
#घोषणा SBREG_SMBCTRL_DNV	0xcf000c

/* Host status bits क्रम SMBPCISTS */
#घोषणा SMBPCISTS_INTS		BIT(3)

/* Control bits क्रम SMBPCICTL */
#घोषणा SMBPCICTL_INTDIS	BIT(10)

/* Host configuration bits क्रम SMBHSTCFG */
#घोषणा SMBHSTCFG_HST_EN	BIT(0)
#घोषणा SMBHSTCFG_SMB_SMI_EN	BIT(1)
#घोषणा SMBHSTCFG_I2C_EN	BIT(2)
#घोषणा SMBHSTCFG_SPD_WD	BIT(4)

/* TCO configuration bits क्रम TCOCTL */
#घोषणा TCOCTL_EN		BIT(8)

/* Auxiliary status रेजिस्टर bits, ICH4+ only */
#घोषणा SMBAUXSTS_CRCE		BIT(0)
#घोषणा SMBAUXSTS_STCO		BIT(1)

/* Auxiliary control रेजिस्टर bits, ICH4+ only */
#घोषणा SMBAUXCTL_CRC		BIT(0)
#घोषणा SMBAUXCTL_E32B		BIT(1)

/* Other settings */
#घोषणा MAX_RETRIES		400

/* I801 command स्थिरants */
#घोषणा I801_QUICK		0x00
#घोषणा I801_BYTE		0x04
#घोषणा I801_BYTE_DATA		0x08
#घोषणा I801_WORD_DATA		0x0C
#घोषणा I801_PROC_CALL		0x10	/* unimplemented */
#घोषणा I801_BLOCK_DATA		0x14
#घोषणा I801_I2C_BLOCK_DATA	0x18	/* ICH5 and later */
#घोषणा I801_BLOCK_PROC_CALL	0x1C

/* I801 Host Control रेजिस्टर bits */
#घोषणा SMBHSTCNT_INTREN	BIT(0)
#घोषणा SMBHSTCNT_KILL		BIT(1)
#घोषणा SMBHSTCNT_LAST_BYTE	BIT(5)
#घोषणा SMBHSTCNT_START		BIT(6)
#घोषणा SMBHSTCNT_PEC_EN	BIT(7)	/* ICH3 and later */

/* I801 Hosts Status रेजिस्टर bits */
#घोषणा SMBHSTSTS_BYTE_DONE	BIT(7)
#घोषणा SMBHSTSTS_INUSE_STS	BIT(6)
#घोषणा SMBHSTSTS_SMBALERT_STS	BIT(5)
#घोषणा SMBHSTSTS_FAILED	BIT(4)
#घोषणा SMBHSTSTS_BUS_ERR	BIT(3)
#घोषणा SMBHSTSTS_DEV_ERR	BIT(2)
#घोषणा SMBHSTSTS_INTR		BIT(1)
#घोषणा SMBHSTSTS_HOST_BUSY	BIT(0)

/* Host Notअगरy Status रेजिस्टर bits */
#घोषणा SMBSLVSTS_HST_NTFY_STS	BIT(0)

/* Host Notअगरy Command रेजिस्टर bits */
#घोषणा SMBSLVCMD_HST_NTFY_INTREN	BIT(0)

#घोषणा STATUS_ERROR_FLAGS	(SMBHSTSTS_FAILED | SMBHSTSTS_BUS_ERR | \
				 SMBHSTSTS_DEV_ERR)

#घोषणा STATUS_FLAGS		(SMBHSTSTS_BYTE_DONE | SMBHSTSTS_INTR | \
				 STATUS_ERROR_FLAGS)

/* Older devices have their ID defined in <linux/pci_ids.h> */
#घोषणा PCI_DEVICE_ID_INTEL_COMETLAKE_SMBUS		0x02a3
#घोषणा PCI_DEVICE_ID_INTEL_COMETLAKE_H_SMBUS		0x06a3
#घोषणा PCI_DEVICE_ID_INTEL_BAYTRAIL_SMBUS		0x0f12
#घोषणा PCI_DEVICE_ID_INTEL_CDF_SMBUS			0x18df
#घोषणा PCI_DEVICE_ID_INTEL_DNV_SMBUS			0x19df
#घोषणा PCI_DEVICE_ID_INTEL_EBG_SMBUS			0x1bc9
#घोषणा PCI_DEVICE_ID_INTEL_COUGARPOINT_SMBUS		0x1c22
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS		0x1d22
/* Patsburg also has three 'Integrated Device Function' SMBus controllers */
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF0		0x1d70
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF1		0x1d71
#घोषणा PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF2		0x1d72
#घोषणा PCI_DEVICE_ID_INTEL_PANTHERPOINT_SMBUS		0x1e22
#घोषणा PCI_DEVICE_ID_INTEL_AVOTON_SMBUS		0x1f3c
#घोषणा PCI_DEVICE_ID_INTEL_BRASWELL_SMBUS		0x2292
#घोषणा PCI_DEVICE_ID_INTEL_DH89XXCC_SMBUS		0x2330
#घोषणा PCI_DEVICE_ID_INTEL_COLETOCREEK_SMBUS		0x23b0
#घोषणा PCI_DEVICE_ID_INTEL_GEMINILAKE_SMBUS		0x31d4
#घोषणा PCI_DEVICE_ID_INTEL_ICELAKE_LP_SMBUS		0x34a3
#घोषणा PCI_DEVICE_ID_INTEL_5_3400_SERIES_SMBUS		0x3b30
#घोषणा PCI_DEVICE_ID_INTEL_TIGERLAKE_H_SMBUS		0x43a3
#घोषणा PCI_DEVICE_ID_INTEL_ELKHART_LAKE_SMBUS		0x4b23
#घोषणा PCI_DEVICE_ID_INTEL_JASPER_LAKE_SMBUS		0x4da3
#घोषणा PCI_DEVICE_ID_INTEL_ALDER_LAKE_P_SMBUS		0x51a3
#घोषणा PCI_DEVICE_ID_INTEL_ALDER_LAKE_M_SMBUS		0x54a3
#घोषणा PCI_DEVICE_ID_INTEL_BROXTON_SMBUS		0x5ad4
#घोषणा PCI_DEVICE_ID_INTEL_ALDER_LAKE_S_SMBUS		0x7aa3
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_SMBUS		0x8c22
#घोषणा PCI_DEVICE_ID_INTEL_WILDCATPOINT_SMBUS		0x8ca2
#घोषणा PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS		0x8d22
#घोषणा PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS0		0x8d7d
#घोषणा PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS1		0x8d7e
#घोषणा PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS2		0x8d7f
#घोषणा PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_SMBUS		0x9c22
#घोषणा PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_SMBUS	0x9ca2
#घोषणा PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_SMBUS	0x9d23
#घोषणा PCI_DEVICE_ID_INTEL_CANNONLAKE_LP_SMBUS		0x9da3
#घोषणा PCI_DEVICE_ID_INTEL_TIGERLAKE_LP_SMBUS		0xa0a3
#घोषणा PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_SMBUS	0xa123
#घोषणा PCI_DEVICE_ID_INTEL_LEWISBURG_SMBUS		0xa1a3
#घोषणा PCI_DEVICE_ID_INTEL_LEWISBURG_SSKU_SMBUS	0xa223
#घोषणा PCI_DEVICE_ID_INTEL_KABYLAKE_PCH_H_SMBUS	0xa2a3
#घोषणा PCI_DEVICE_ID_INTEL_CANNONLAKE_H_SMBUS		0xa323
#घोषणा PCI_DEVICE_ID_INTEL_COMETLAKE_V_SMBUS		0xa3a3

काष्ठा i801_mux_config अणु
	अक्षर *gpio_chip;
	अचिन्हित values[3];
	पूर्णांक n_values;
	अचिन्हित classes[3];
	अचिन्हित gpios[2];		/* Relative to gpio_chip->base */
	पूर्णांक n_gpios;
पूर्ण;

काष्ठा i801_priv अणु
	काष्ठा i2c_adapter adapter;
	अचिन्हित दीर्घ smba;
	अचिन्हित अक्षर original_hstcfg;
	अचिन्हित अक्षर original_slvcmd;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित पूर्णांक features;

	/* isr processing */
	रुको_queue_head_t रुकोq;
	u8 status;

	/* Command state used by isr क्रम byte-by-byte block transactions */
	u8 cmd;
	bool is_पढ़ो;
	पूर्णांक count;
	पूर्णांक len;
	u8 *data;

#अगर IS_ENABLED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
	स्थिर काष्ठा i801_mux_config *mux_drvdata;
	काष्ठा platक्रमm_device *mux_pdev;
	काष्ठा gpiod_lookup_table *lookup;
#पूर्ण_अगर
	काष्ठा platक्रमm_device *tco_pdev;

	/*
	 * If set to true the host controller रेजिस्टरs are reserved क्रम
	 * ACPI AML use. Protected by acpi_lock.
	 */
	bool acpi_reserved;
	काष्ठा mutex acpi_lock;
पूर्ण;

#घोषणा FEATURE_SMBUS_PEC	BIT(0)
#घोषणा FEATURE_BLOCK_BUFFER	BIT(1)
#घोषणा FEATURE_BLOCK_PROC	BIT(2)
#घोषणा FEATURE_I2C_BLOCK_READ	BIT(3)
#घोषणा FEATURE_IRQ		BIT(4)
#घोषणा FEATURE_HOST_NOTIFY	BIT(5)
/* Not really a feature, but it's convenient to handle it as such */
#घोषणा FEATURE_IDF		BIT(15)
#घोषणा FEATURE_TCO_SPT		BIT(16)
#घोषणा FEATURE_TCO_CNL		BIT(17)

अटल स्थिर अक्षर *i801_feature_names[] = अणु
	"SMBus PEC",
	"Block buffer",
	"Block process call",
	"I2C block read",
	"Interrupt",
	"SMBus Host Notify",
पूर्ण;

अटल अचिन्हित पूर्णांक disable_features;
module_param(disable_features, uपूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(disable_features, "Disable selected driver features:\n"
	"\t\t  0x01  disable SMBus PEC\n"
	"\t\t  0x02  disable the block buffer\n"
	"\t\t  0x08  disable the I2C block read functionality\n"
	"\t\t  0x10  don't use interrupts\n"
	"\t\t  0x20  disable SMBus Host Notify ");

/* Make sure the SMBus host is पढ़ोy to start transmitting.
   Return 0 अगर it is, -EBUSY अगर it is not. */
अटल पूर्णांक i801_check_pre(काष्ठा i801_priv *priv)
अणु
	पूर्णांक status;

	status = inb_p(SMBHSTSTS(priv));
	अगर (status & SMBHSTSTS_HOST_BUSY) अणु
		dev_err(&priv->pci_dev->dev, "SMBus is busy, can't use it!\n");
		वापस -EBUSY;
	पूर्ण

	status &= STATUS_FLAGS;
	अगर (status) अणु
		dev_dbg(&priv->pci_dev->dev, "Clearing status flags (%02x)\n",
			status);
		outb_p(status, SMBHSTSTS(priv));
		status = inb_p(SMBHSTSTS(priv)) & STATUS_FLAGS;
		अगर (status) अणु
			dev_err(&priv->pci_dev->dev,
				"Failed clearing status flags (%02x)\n",
				status);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/*
	 * Clear CRC status अगर needed.
	 * During normal operation, i801_check_post() takes care
	 * of it after every operation.  We करो it here only in हाल
	 * the hardware was alपढ़ोy in this state when the driver
	 * started.
	 */
	अगर (priv->features & FEATURE_SMBUS_PEC) अणु
		status = inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE;
		अगर (status) अणु
			dev_dbg(&priv->pci_dev->dev,
				"Clearing aux status flags (%02x)\n", status);
			outb_p(status, SMBAUXSTS(priv));
			status = inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE;
			अगर (status) अणु
				dev_err(&priv->pci_dev->dev,
					"Failed clearing aux status flags (%02x)\n",
					status);
				वापस -EBUSY;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Convert the status रेजिस्टर to an error code, and clear it.
 * Note that status only contains the bits we want to clear, not the
 * actual रेजिस्टर value.
 */
अटल पूर्णांक i801_check_post(काष्ठा i801_priv *priv, पूर्णांक status)
अणु
	पूर्णांक result = 0;

	/*
	 * If the SMBus is still busy, we give up
	 * Note: This समयout condition only happens when using polling
	 * transactions.  For पूर्णांकerrupt operation, NAK/समयout is indicated by
	 * DEV_ERR.
	 */
	अगर (unlikely(status < 0)) अणु
		dev_err(&priv->pci_dev->dev, "Transaction timeout\n");
		/* try to stop the current command */
		dev_dbg(&priv->pci_dev->dev, "Terminating the current operation\n");
		outb_p(SMBHSTCNT_KILL, SMBHSTCNT(priv));
		usleep_range(1000, 2000);
		outb_p(0, SMBHSTCNT(priv));

		/* Check अगर it worked */
		status = inb_p(SMBHSTSTS(priv));
		अगर ((status & SMBHSTSTS_HOST_BUSY) ||
		    !(status & SMBHSTSTS_FAILED))
			dev_err(&priv->pci_dev->dev,
				"Failed terminating the transaction\n");
		outb_p(STATUS_FLAGS, SMBHSTSTS(priv));
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (status & SMBHSTSTS_FAILED) अणु
		result = -EIO;
		dev_err(&priv->pci_dev->dev, "Transaction failed\n");
	पूर्ण
	अगर (status & SMBHSTSTS_DEV_ERR) अणु
		/*
		 * This may be a PEC error, check and clear it.
		 *
		 * AUXSTS is handled dअगरferently from HSTSTS.
		 * For HSTSTS, i801_isr() or i801_रुको_पूर्णांकr()
		 * has alपढ़ोy cleared the error bits in hardware,
		 * and we are passed a copy of the original value
		 * in "status".
		 * For AUXSTS, the hardware रेजिस्टर is left
		 * क्रम us to handle here.
		 * This is asymmetric, slightly अगरfy, but safe,
		 * since all this code is serialized and the CRCE
		 * bit is harmless as दीर्घ as it's cleared beक्रमe
		 * the next operation.
		 */
		अगर ((priv->features & FEATURE_SMBUS_PEC) &&
		    (inb_p(SMBAUXSTS(priv)) & SMBAUXSTS_CRCE)) अणु
			outb_p(SMBAUXSTS_CRCE, SMBAUXSTS(priv));
			result = -EBADMSG;
			dev_dbg(&priv->pci_dev->dev, "PEC error\n");
		पूर्ण अन्यथा अणु
			result = -ENXIO;
			dev_dbg(&priv->pci_dev->dev, "No response\n");
		पूर्ण
	पूर्ण
	अगर (status & SMBHSTSTS_BUS_ERR) अणु
		result = -EAGAIN;
		dev_dbg(&priv->pci_dev->dev, "Lost arbitration\n");
	पूर्ण

	/* Clear status flags except BYTE_DONE, to be cleared by caller */
	outb_p(status, SMBHSTSTS(priv));

	वापस result;
पूर्ण

/* Wait क्रम BUSY being cleared and either INTR or an error flag being set */
अटल पूर्णांक i801_रुको_पूर्णांकr(काष्ठा i801_priv *priv)
अणु
	पूर्णांक समयout = 0;
	पूर्णांक status;

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	पूर्ण जबतक (((status & SMBHSTSTS_HOST_BUSY) ||
		  !(status & (STATUS_ERROR_FLAGS | SMBHSTSTS_INTR))) &&
		 (समयout++ < MAX_RETRIES));

	अगर (समयout > MAX_RETRIES) अणु
		dev_dbg(&priv->pci_dev->dev, "INTR Timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस status & (STATUS_ERROR_FLAGS | SMBHSTSTS_INTR);
पूर्ण

/* Wait क्रम either BYTE_DONE or an error flag being set */
अटल पूर्णांक i801_रुको_byte_करोne(काष्ठा i801_priv *priv)
अणु
	पूर्णांक समयout = 0;
	पूर्णांक status;

	/* We will always रुको क्रम a fraction of a second! */
	करो अणु
		usleep_range(250, 500);
		status = inb_p(SMBHSTSTS(priv));
	पूर्ण जबतक (!(status & (STATUS_ERROR_FLAGS | SMBHSTSTS_BYTE_DONE)) &&
		 (समयout++ < MAX_RETRIES));

	अगर (समयout > MAX_RETRIES) अणु
		dev_dbg(&priv->pci_dev->dev, "BYTE_DONE Timeout!\n");
		वापस -ETIMEDOUT;
	पूर्ण
	वापस status & STATUS_ERROR_FLAGS;
पूर्ण

अटल पूर्णांक i801_transaction(काष्ठा i801_priv *priv, पूर्णांक xact)
अणु
	पूर्णांक status;
	पूर्णांक result;
	स्थिर काष्ठा i2c_adapter *adap = &priv->adapter;

	result = i801_check_pre(priv);
	अगर (result < 0)
		वापस result;

	अगर (priv->features & FEATURE_IRQ) अणु
		outb_p(xact | SMBHSTCNT_INTREN | SMBHSTCNT_START,
		       SMBHSTCNT(priv));
		result = रुको_event_समयout(priv->रुकोq,
					    (status = priv->status),
					    adap->समयout);
		अगर (!result) अणु
			status = -ETIMEDOUT;
			dev_warn(&priv->pci_dev->dev,
				 "Timeout waiting for interrupt!\n");
		पूर्ण
		priv->status = 0;
		वापस i801_check_post(priv, status);
	पूर्ण

	/* the current contents of SMBHSTCNT can be overwritten, since PEC,
	 * SMBSCMD are passed in xact */
	outb_p(xact | SMBHSTCNT_START, SMBHSTCNT(priv));

	status = i801_रुको_पूर्णांकr(priv);
	वापस i801_check_post(priv, status);
पूर्ण

अटल पूर्णांक i801_block_transaction_by_block(काष्ठा i801_priv *priv,
					   जोड़ i2c_smbus_data *data,
					   अक्षर पढ़ो_ग_लिखो, पूर्णांक command,
					   पूर्णांक hwpec)
अणु
	पूर्णांक i, len;
	पूर्णांक status;
	पूर्णांक xact = hwpec ? SMBHSTCNT_PEC_EN : 0;

	चयन (command) अणु
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		xact |= I801_BLOCK_PROC_CALL;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		xact |= I801_BLOCK_DATA;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	inb_p(SMBHSTCNT(priv)); /* reset the data buffer index */

	/* Use 32-byte buffer to process this transaction */
	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		len = data->block[0];
		outb_p(len, SMBHSTDAT0(priv));
		क्रम (i = 0; i < len; i++)
			outb_p(data->block[i+1], SMBBLKDAT(priv));
	पूर्ण

	status = i801_transaction(priv, xact);
	अगर (status)
		वापस status;

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ ||
	    command == I2C_SMBUS_BLOCK_PROC_CALL) अणु
		len = inb_p(SMBHSTDAT0(priv));
		अगर (len < 1 || len > I2C_SMBUS_BLOCK_MAX)
			वापस -EPROTO;

		data->block[0] = len;
		क्रम (i = 0; i < len; i++)
			data->block[i + 1] = inb_p(SMBBLKDAT(priv));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम i801_isr_byte_करोne(काष्ठा i801_priv *priv)
अणु
	अगर (priv->is_पढ़ो) अणु
		/* For SMBus block पढ़ोs, length is received with first byte */
		अगर (((priv->cmd & 0x1c) == I801_BLOCK_DATA) &&
		    (priv->count == 0)) अणु
			priv->len = inb_p(SMBHSTDAT0(priv));
			अगर (priv->len < 1 || priv->len > I2C_SMBUS_BLOCK_MAX) अणु
				dev_err(&priv->pci_dev->dev,
					"Illegal SMBus block read size %d\n",
					priv->len);
				/* FIXME: Recover */
				priv->len = I2C_SMBUS_BLOCK_MAX;
			पूर्ण अन्यथा अणु
				dev_dbg(&priv->pci_dev->dev,
					"SMBus block read size is %d\n",
					priv->len);
			पूर्ण
			priv->data[-1] = priv->len;
		पूर्ण

		/* Read next byte */
		अगर (priv->count < priv->len)
			priv->data[priv->count++] = inb(SMBBLKDAT(priv));
		अन्यथा
			dev_dbg(&priv->pci_dev->dev,
				"Discarding extra byte on block read\n");

		/* Set LAST_BYTE क्रम last byte of पढ़ो transaction */
		अगर (priv->count == priv->len - 1)
			outb_p(priv->cmd | SMBHSTCNT_LAST_BYTE,
			       SMBHSTCNT(priv));
	पूर्ण अन्यथा अगर (priv->count < priv->len - 1) अणु
		/* Write next byte, except क्रम IRQ after last byte */
		outb_p(priv->data[++priv->count], SMBBLKDAT(priv));
	पूर्ण

	/* Clear BYTE_DONE to जारी with next byte */
	outb_p(SMBHSTSTS_BYTE_DONE, SMBHSTSTS(priv));
पूर्ण

अटल irqवापस_t i801_host_notअगरy_isr(काष्ठा i801_priv *priv)
अणु
	अचिन्हित लघु addr;

	addr = inb_p(SMBNTFDADD(priv)) >> 1;

	/*
	 * With the tested platक्रमms, पढ़ोing SMBNTFDDAT (22 + (p)->smba)
	 * always वापसs 0. Our current implementation करोesn't provide
	 * data, so we just ignore it.
	 */
	i2c_handle_smbus_host_notअगरy(&priv->adapter, addr);

	/* clear Host Notअगरy bit and वापस */
	outb_p(SMBSLVSTS_HST_NTFY_STS, SMBSLVSTS(priv));
	वापस IRQ_HANDLED;
पूर्ण

/*
 * There are three kinds of पूर्णांकerrupts:
 *
 * 1) i801 संकेतs transaction completion with one of these पूर्णांकerrupts:
 *      INTR - Success
 *      DEV_ERR - Invalid command, NAK or communication समयout
 *      BUS_ERR - SMI# transaction collision
 *      FAILED - transaction was canceled due to a KILL request
 *    When any of these occur, update ->status and wake up the रुकोq.
 *    ->status must be cleared beक्रमe kicking off the next transaction.
 *
 * 2) For byte-by-byte (I2C पढ़ो/ग_लिखो) transactions, one BYTE_DONE पूर्णांकerrupt
 *    occurs क्रम each byte of a byte-by-byte to prepare the next byte.
 *
 * 3) Host Notअगरy पूर्णांकerrupts
 */
अटल irqवापस_t i801_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i801_priv *priv = dev_id;
	u16 pcists;
	u8 status;

	/* Confirm this is our पूर्णांकerrupt */
	pci_पढ़ो_config_word(priv->pci_dev, SMBPCISTS, &pcists);
	अगर (!(pcists & SMBPCISTS_INTS))
		वापस IRQ_NONE;

	अगर (priv->features & FEATURE_HOST_NOTIFY) अणु
		status = inb_p(SMBSLVSTS(priv));
		अगर (status & SMBSLVSTS_HST_NTFY_STS)
			वापस i801_host_notअगरy_isr(priv);
	पूर्ण

	status = inb_p(SMBHSTSTS(priv));
	अगर (status & SMBHSTSTS_BYTE_DONE)
		i801_isr_byte_करोne(priv);

	/*
	 * Clear irq sources and report transaction result.
	 * ->status must be cleared beक्रमe the next transaction is started.
	 */
	status &= SMBHSTSTS_INTR | STATUS_ERROR_FLAGS;
	अगर (status) अणु
		outb_p(status, SMBHSTSTS(priv));
		priv->status = status;
		wake_up(&priv->रुकोq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * For "byte-by-byte" block transactions:
 *   I2C ग_लिखो uses cmd=I801_BLOCK_DATA, I2C_EN=1
 *   I2C पढ़ो uses cmd=I801_I2C_BLOCK_DATA
 */
अटल पूर्णांक i801_block_transaction_byte_by_byte(काष्ठा i801_priv *priv,
					       जोड़ i2c_smbus_data *data,
					       अक्षर पढ़ो_ग_लिखो, पूर्णांक command,
					       पूर्णांक hwpec)
अणु
	पूर्णांक i, len;
	पूर्णांक smbcmd;
	पूर्णांक status;
	पूर्णांक result;
	स्थिर काष्ठा i2c_adapter *adap = &priv->adapter;

	अगर (command == I2C_SMBUS_BLOCK_PROC_CALL)
		वापस -EOPNOTSUPP;

	result = i801_check_pre(priv);
	अगर (result < 0)
		वापस result;

	len = data->block[0];

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		outb_p(len, SMBHSTDAT0(priv));
		outb_p(data->block[1], SMBBLKDAT(priv));
	पूर्ण

	अगर (command == I2C_SMBUS_I2C_BLOCK_DATA &&
	    पढ़ो_ग_लिखो == I2C_SMBUS_READ)
		smbcmd = I801_I2C_BLOCK_DATA;
	अन्यथा
		smbcmd = I801_BLOCK_DATA;

	अगर (priv->features & FEATURE_IRQ) अणु
		priv->is_पढ़ो = (पढ़ो_ग_लिखो == I2C_SMBUS_READ);
		अगर (len == 1 && priv->is_पढ़ो)
			smbcmd |= SMBHSTCNT_LAST_BYTE;
		priv->cmd = smbcmd | SMBHSTCNT_INTREN;
		priv->len = len;
		priv->count = 0;
		priv->data = &data->block[1];

		outb_p(priv->cmd | SMBHSTCNT_START, SMBHSTCNT(priv));
		result = रुको_event_समयout(priv->रुकोq,
					    (status = priv->status),
					    adap->समयout);
		अगर (!result) अणु
			status = -ETIMEDOUT;
			dev_warn(&priv->pci_dev->dev,
				 "Timeout waiting for interrupt!\n");
		पूर्ण
		priv->status = 0;
		वापस i801_check_post(priv, status);
	पूर्ण

	क्रम (i = 1; i <= len; i++) अणु
		अगर (i == len && पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			smbcmd |= SMBHSTCNT_LAST_BYTE;
		outb_p(smbcmd, SMBHSTCNT(priv));

		अगर (i == 1)
			outb_p(inb(SMBHSTCNT(priv)) | SMBHSTCNT_START,
			       SMBHSTCNT(priv));

		status = i801_रुको_byte_करोne(priv);
		अगर (status)
			जाओ निकास;

		अगर (i == 1 && पढ़ो_ग_लिखो == I2C_SMBUS_READ
		 && command != I2C_SMBUS_I2C_BLOCK_DATA) अणु
			len = inb_p(SMBHSTDAT0(priv));
			अगर (len < 1 || len > I2C_SMBUS_BLOCK_MAX) अणु
				dev_err(&priv->pci_dev->dev,
					"Illegal SMBus block read size %d\n",
					len);
				/* Recover */
				जबतक (inb_p(SMBHSTSTS(priv)) &
				       SMBHSTSTS_HOST_BUSY)
					outb_p(SMBHSTSTS_BYTE_DONE,
					       SMBHSTSTS(priv));
				outb_p(SMBHSTSTS_INTR, SMBHSTSTS(priv));
				वापस -EPROTO;
			पूर्ण
			data->block[0] = len;
		पूर्ण

		/* Retrieve/store value in SMBBLKDAT */
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ)
			data->block[i] = inb_p(SMBBLKDAT(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE && i+1 <= len)
			outb_p(data->block[i+1], SMBBLKDAT(priv));

		/* संकेतs SMBBLKDAT पढ़ोy */
		outb_p(SMBHSTSTS_BYTE_DONE, SMBHSTSTS(priv));
	पूर्ण

	status = i801_रुको_पूर्णांकr(priv);
निकास:
	वापस i801_check_post(priv, status);
पूर्ण

अटल पूर्णांक i801_set_block_buffer_mode(काष्ठा i801_priv *priv)
अणु
	outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_E32B, SMBAUXCTL(priv));
	अगर ((inb_p(SMBAUXCTL(priv)) & SMBAUXCTL_E32B) == 0)
		वापस -EIO;
	वापस 0;
पूर्ण

/* Block transaction function */
अटल पूर्णांक i801_block_transaction(काष्ठा i801_priv *priv,
				  जोड़ i2c_smbus_data *data, अक्षर पढ़ो_ग_लिखो,
				  पूर्णांक command, पूर्णांक hwpec)
अणु
	पूर्णांक result = 0;
	अचिन्हित अक्षर hostc;

	अगर (command == I2C_SMBUS_I2C_BLOCK_DATA) अणु
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			/* set I2C_EN bit in configuration रेजिस्टर */
			pci_पढ़ो_config_byte(priv->pci_dev, SMBHSTCFG, &hostc);
			pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG,
					      hostc | SMBHSTCFG_I2C_EN);
		पूर्ण अन्यथा अगर (!(priv->features & FEATURE_I2C_BLOCK_READ)) अणु
			dev_err(&priv->pci_dev->dev,
				"I2C block read is unsupported!\n");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE
	 || command == I2C_SMBUS_I2C_BLOCK_DATA) अणु
		अगर (data->block[0] < 1)
			data->block[0] = 1;
		अगर (data->block[0] > I2C_SMBUS_BLOCK_MAX)
			data->block[0] = I2C_SMBUS_BLOCK_MAX;
	पूर्ण अन्यथा अणु
		data->block[0] = 32;	/* max क्रम SMBus block पढ़ोs */
	पूर्ण

	/* Experience has shown that the block buffer can only be used क्रम
	   SMBus (not I2C) block transactions, even though the datasheet
	   करोesn't mention this limitation. */
	अगर ((priv->features & FEATURE_BLOCK_BUFFER)
	 && command != I2C_SMBUS_I2C_BLOCK_DATA
	 && i801_set_block_buffer_mode(priv) == 0)
		result = i801_block_transaction_by_block(priv, data,
							 पढ़ो_ग_लिखो,
							 command, hwpec);
	अन्यथा
		result = i801_block_transaction_byte_by_byte(priv, data,
							     पढ़ो_ग_लिखो,
							     command, hwpec);

	अगर (command == I2C_SMBUS_I2C_BLOCK_DATA
	 && पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
		/* restore saved configuration रेजिस्टर value */
		pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG, hostc);
	पूर्ण
	वापस result;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 i801_access(काष्ठा i2c_adapter *adap, u16 addr,
		       अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो, u8 command,
		       पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	पूर्णांक hwpec;
	पूर्णांक block = 0;
	पूर्णांक ret = 0, xact = 0;
	काष्ठा i801_priv *priv = i2c_get_adapdata(adap);

	mutex_lock(&priv->acpi_lock);
	अगर (priv->acpi_reserved) अणु
		mutex_unlock(&priv->acpi_lock);
		वापस -EBUSY;
	पूर्ण

	pm_runसमय_get_sync(&priv->pci_dev->dev);

	hwpec = (priv->features & FEATURE_SMBUS_PEC) && (flags & I2C_CLIENT_PEC)
		&& size != I2C_SMBUS_QUICK
		&& size != I2C_SMBUS_I2C_BLOCK_DATA;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		xact = I801_QUICK;
		अवरोध;
	हाल I2C_SMBUS_BYTE:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(command, SMBHSTCMD(priv));
		xact = I801_BYTE;
		अवरोध;
	हाल I2C_SMBUS_BYTE_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE)
			outb_p(data->byte, SMBHSTDAT0(priv));
		xact = I801_BYTE_DATA;
		अवरोध;
	हाल I2C_SMBUS_WORD_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			outb_p(data->word & 0xff, SMBHSTDAT0(priv));
			outb_p((data->word & 0xff00) >> 8, SMBHSTDAT1(priv));
		पूर्ण
		xact = I801_WORD_DATA;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_DATA:
		outb_p(((addr & 0x7f) << 1) | (पढ़ो_ग_लिखो & 0x01),
		       SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		अवरोध;
	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		/*
		 * NB: page 240 of ICH5 datasheet shows that the R/#W
		 * bit should be cleared here, even when पढ़ोing.
		 * However अगर SPD Write Disable is set (Lynx Poपूर्णांक and later),
		 * the पढ़ो will fail अगर we करोn't set the R/#W bit.
		 */
		outb_p(((addr & 0x7f) << 1) |
		       ((priv->original_hstcfg & SMBHSTCFG_SPD_WD) ?
			(पढ़ो_ग_लिखो & 0x01) : 0),
		       SMBHSTADD(priv));
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_READ) अणु
			/* NB: page 240 of ICH5 datasheet also shows
			 * that DATA1 is the cmd field when पढ़ोing */
			outb_p(command, SMBHSTDAT1(priv));
		पूर्ण अन्यथा
			outb_p(command, SMBHSTCMD(priv));
		block = 1;
		अवरोध;
	हाल I2C_SMBUS_BLOCK_PROC_CALL:
		/*
		 * Bit 0 of the slave address रेजिस्टर always indicate a ग_लिखो
		 * command.
		 */
		outb_p((addr & 0x7f) << 1, SMBHSTADD(priv));
		outb_p(command, SMBHSTCMD(priv));
		block = 1;
		अवरोध;
	शेष:
		dev_err(&priv->pci_dev->dev, "Unsupported transaction %d\n",
			size);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (hwpec)	/* enable/disable hardware PEC */
		outb_p(inb_p(SMBAUXCTL(priv)) | SMBAUXCTL_CRC, SMBAUXCTL(priv));
	अन्यथा
		outb_p(inb_p(SMBAUXCTL(priv)) & (~SMBAUXCTL_CRC),
		       SMBAUXCTL(priv));

	अगर (block)
		ret = i801_block_transaction(priv, data, पढ़ो_ग_लिखो, size,
					     hwpec);
	अन्यथा
		ret = i801_transaction(priv, xact);

	/* Some BIOSes करोn't like it when PEC is enabled at reboot or resume
	   समय, so we क्रमcibly disable it after every transaction. Turn off
	   E32B क्रम the same reason. */
	अगर (hwpec || block)
		outb_p(inb_p(SMBAUXCTL(priv)) &
		       ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B), SMBAUXCTL(priv));

	अगर (block)
		जाओ out;
	अगर (ret)
		जाओ out;
	अगर ((पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) || (xact == I801_QUICK))
		जाओ out;

	चयन (xact & 0x7f) अणु
	हाल I801_BYTE:	/* Result put in SMBHSTDAT0 */
	हाल I801_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0(priv));
		अवरोध;
	हाल I801_WORD_DATA:
		data->word = inb_p(SMBHSTDAT0(priv)) +
			     (inb_p(SMBHSTDAT1(priv)) << 8);
		अवरोध;
	पूर्ण

out:
	pm_runसमय_mark_last_busy(&priv->pci_dev->dev);
	pm_runसमय_put_स्वतःsuspend(&priv->pci_dev->dev);
	mutex_unlock(&priv->acpi_lock);
	वापस ret;
पूर्ण


अटल u32 i801_func(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i801_priv *priv = i2c_get_adapdata(adapter);

	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_WRITE_I2C_BLOCK |
	       ((priv->features & FEATURE_SMBUS_PEC) ? I2C_FUNC_SMBUS_PEC : 0) |
	       ((priv->features & FEATURE_BLOCK_PROC) ?
		I2C_FUNC_SMBUS_BLOCK_PROC_CALL : 0) |
	       ((priv->features & FEATURE_I2C_BLOCK_READ) ?
		I2C_FUNC_SMBUS_READ_I2C_BLOCK : 0) |
	       ((priv->features & FEATURE_HOST_NOTIFY) ?
		I2C_FUNC_SMBUS_HOST_NOTIFY : 0);
पूर्ण

अटल व्योम i801_enable_host_notअगरy(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i801_priv *priv = i2c_get_adapdata(adapter);

	अगर (!(priv->features & FEATURE_HOST_NOTIFY))
		वापस;

	अगर (!(SMBSLVCMD_HST_NTFY_INTREN & priv->original_slvcmd))
		outb_p(SMBSLVCMD_HST_NTFY_INTREN | priv->original_slvcmd,
		       SMBSLVCMD(priv));

	/* clear Host Notअगरy bit to allow a new notअगरication */
	outb_p(SMBSLVSTS_HST_NTFY_STS, SMBSLVSTS(priv));
पूर्ण

अटल व्योम i801_disable_host_notअगरy(काष्ठा i801_priv *priv)
अणु
	अगर (!(priv->features & FEATURE_HOST_NOTIFY))
		वापस;

	outb_p(priv->original_slvcmd, SMBSLVCMD(priv));
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.smbus_xfer	= i801_access,
	.functionality	= i801_func,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id i801_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801AA_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801AB_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801BA_2) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801CA_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801DB_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_82801EB_3) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB_4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH6_16) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH7_17) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ESB2_17) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH8_5) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH9_6) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EP80579_1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH10_4) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICH10_5) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5_3400_SERIES_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_COUGARPOINT_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF2) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_DH89XXCC_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_PANTHERPOINT_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LYNXPOINT_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LYNXPOINT_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_AVOTON_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS0) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS1) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS2) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_COLETOCREEK_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_GEMINILAKE_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WILDCATPOINT_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_WILDCATPOINT_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BAYTRAIL_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BRASWELL_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CDF_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_DNV_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_EBG_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BROXTON_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LEWISBURG_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_LEWISBURG_SSKU_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_KABYLAKE_PCH_H_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CANNONLAKE_H_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_CANNONLAKE_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ICELAKE_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_COMETLAKE_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_COMETLAKE_H_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_COMETLAKE_V_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ELKHART_LAKE_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TIGERLAKE_LP_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_TIGERLAKE_H_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_JASPER_LAKE_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ALDER_LAKE_S_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ALDER_LAKE_P_SMBUS) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_ALDER_LAKE_M_SMBUS) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, i801_ids);

#अगर defined CONFIG_X86 && defined CONFIG_DMI
अटल अचिन्हित अक्षर apanel_addr;

/* Scan the प्रणाली ROM क्रम the signature "FJKEYINF" */
अटल __init स्थिर व्योम __iomem *bios_signature(स्थिर व्योम __iomem *bios)
अणु
	sमाप_प्रकार offset;
	स्थिर अचिन्हित अक्षर signature[] = "FJKEYINF";

	क्रम (offset = 0; offset < 0x10000; offset += 0x10) अणु
		अगर (check_signature(bios + offset, signature,
				    माप(signature)-1))
			वापस bios + offset;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __init input_apanel_init(व्योम)
अणु
	व्योम __iomem *bios;
	स्थिर व्योम __iomem *p;

	bios = ioremap(0xF0000, 0x10000); /* Can't fail */
	p = bios_signature(bios);
	अगर (p) अणु
		/* just use the first address */
		apanel_addr = पढ़ोb(p + 8 + 3) >> 1;
	पूर्ण
	iounmap(bios);
पूर्ण

काष्ठा dmi_onboard_device_info अणु
	स्थिर अक्षर *name;
	u8 type;
	अचिन्हित लघु i2c_addr;
	स्थिर अक्षर *i2c_type;
पूर्ण;

अटल स्थिर काष्ठा dmi_onboard_device_info dmi_devices[] = अणु
	अणु "Syleus", DMI_DEV_TYPE_OTHER, 0x73, "fscsyl" पूर्ण,
	अणु "Hermes", DMI_DEV_TYPE_OTHER, 0x73, "fscher" पूर्ण,
	अणु "Hades",  DMI_DEV_TYPE_OTHER, 0x73, "fschds" पूर्ण,
पूर्ण;

अटल व्योम dmi_check_onboard_device(u8 type, स्थिर अक्षर *name,
				     काष्ठा i2c_adapter *adap)
अणु
	पूर्णांक i;
	काष्ठा i2c_board_info info;

	क्रम (i = 0; i < ARRAY_SIZE(dmi_devices); i++) अणु
		/* & ~0x80, ignore enabled/disabled bit */
		अगर ((type & ~0x80) != dmi_devices[i].type)
			जारी;
		अगर (strहालcmp(name, dmi_devices[i].name))
			जारी;

		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		info.addr = dmi_devices[i].i2c_addr;
		strlcpy(info.type, dmi_devices[i].i2c_type, I2C_NAME_SIZE);
		i2c_new_client_device(adap, &info);
		अवरोध;
	पूर्ण
पूर्ण

/* We use our own function to check क्रम onboard devices instead of
   dmi_find_device() as some buggy BIOS's have the devices we are पूर्णांकerested
   in marked as disabled */
अटल व्योम dmi_check_onboard_devices(स्थिर काष्ठा dmi_header *dm, व्योम *adap)
अणु
	पूर्णांक i, count;

	अगर (dm->type != 10)
		वापस;

	count = (dm->length - माप(काष्ठा dmi_header)) / 2;
	क्रम (i = 0; i < count; i++) अणु
		स्थिर u8 *d = (अक्षर *)(dm + 1) + (i * 2);
		स्थिर अक्षर *name = ((अक्षर *) dm) + dm->length;
		u8 type = d[0];
		u8 s = d[1];

		अगर (!s)
			जारी;
		s--;
		जबतक (s > 0 && name[0]) अणु
			name += म_माप(name) + 1;
			s--;
		पूर्ण
		अगर (name[0] == 0) /* Bogus string reference */
			जारी;

		dmi_check_onboard_device(type, name, adap);
	पूर्ण
पूर्ण

/* NOTE: Keep this list in sync with drivers/platक्रमm/x86/dell-smo8800.c */
अटल स्थिर अक्षर *स्थिर acpi_smo8800_ids[] = अणु
	"SMO8800",
	"SMO8801",
	"SMO8810",
	"SMO8811",
	"SMO8820",
	"SMO8821",
	"SMO8830",
	"SMO8831",
पूर्ण;

अटल acpi_status check_acpi_smo88xx_device(acpi_handle obj_handle,
					     u32 nesting_level,
					     व्योम *context,
					     व्योम **वापस_value)
अणु
	काष्ठा acpi_device_info *info;
	acpi_status status;
	अक्षर *hid;
	पूर्णांक i;

	status = acpi_get_object_info(obj_handle, &info);
	अगर (ACPI_FAILURE(status))
		वापस AE_OK;

	अगर (!(info->valid & ACPI_VALID_HID))
		जाओ smo88xx_not_found;

	hid = info->hardware_id.string;
	अगर (!hid)
		जाओ smo88xx_not_found;

	i = match_string(acpi_smo8800_ids, ARRAY_SIZE(acpi_smo8800_ids), hid);
	अगर (i < 0)
		जाओ smo88xx_not_found;

	kमुक्त(info);

	*((bool *)वापस_value) = true;
	वापस AE_CTRL_TERMINATE;

smo88xx_not_found:
	kमुक्त(info);
	वापस AE_OK;
पूर्ण

अटल bool is_dell_प्रणाली_with_lis3lv02d(व्योम)
अणु
	bool found;
	स्थिर अक्षर *venकरोr;

	venकरोr = dmi_get_प्रणाली_info(DMI_SYS_VENDOR);
	अगर (!venकरोr || म_भेद(venकरोr, "Dell Inc."))
		वापस false;

	/*
	 * Check that ACPI device SMO88xx is present and is functioning.
	 * Function acpi_get_devices() alपढ़ोy filters all ACPI devices
	 * which are not present or are not functioning.
	 * ACPI device SMO88xx represents our ST microelectronics lis3lv02d
	 * accelerometer but unक्रमtunately ACPI करोes not provide any other
	 * inक्रमmation (like I2C address).
	 */
	found = false;
	acpi_get_devices(शून्य, check_acpi_smo88xx_device, शून्य,
			 (व्योम **)&found);

	वापस found;
पूर्ण

/*
 * Accelerometer's I2C address is not specअगरied in DMI nor ACPI,
 * so it is needed to define mapping table based on DMI product names.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *dmi_product_name;
	अचिन्हित लघु i2c_addr;
पूर्ण dell_lis3lv02d_devices[] = अणु
	/*
	 * Dell platक्रमm team told us that these Latitude devices have
	 * ST microelectronics accelerometer at I2C address 0x29.
	 */
	अणु "Latitude E5250",     0x29 पूर्ण,
	अणु "Latitude E5450",     0x29 पूर्ण,
	अणु "Latitude E5550",     0x29 पूर्ण,
	अणु "Latitude E6440",     0x29 पूर्ण,
	अणु "Latitude E6440 ATG", 0x29 पूर्ण,
	अणु "Latitude E6540",     0x29 पूर्ण,
	/*
	 * Additional inभागidual entries were added after verअगरication.
	 */
	अणु "Latitude 5480",      0x29 पूर्ण,
	अणु "Vostro V131",        0x1d पूर्ण,
पूर्ण;

अटल व्योम रेजिस्टर_dell_lis3lv02d_i2c_device(काष्ठा i801_priv *priv)
अणु
	काष्ठा i2c_board_info info;
	स्थिर अक्षर *dmi_product_name;
	पूर्णांक i;

	dmi_product_name = dmi_get_प्रणाली_info(DMI_PRODUCT_NAME);
	क्रम (i = 0; i < ARRAY_SIZE(dell_lis3lv02d_devices); ++i) अणु
		अगर (म_भेद(dmi_product_name,
			   dell_lis3lv02d_devices[i].dmi_product_name) == 0)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(dell_lis3lv02d_devices)) अणु
		dev_warn(&priv->pci_dev->dev,
			 "Accelerometer lis3lv02d is present on SMBus but its"
			 " address is unknown, skipping registration\n");
		वापस;
	पूर्ण

	स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
	info.addr = dell_lis3lv02d_devices[i].i2c_addr;
	strlcpy(info.type, "lis3lv02d", I2C_NAME_SIZE);
	i2c_new_client_device(&priv->adapter, &info);
पूर्ण

/* Register optional slaves */
अटल व्योम i801_probe_optional_slaves(काष्ठा i801_priv *priv)
अणु
	/* Only रेजिस्टर slaves on मुख्य SMBus channel */
	अगर (priv->features & FEATURE_IDF)
		वापस;

	अगर (apanel_addr) अणु
		काष्ठा i2c_board_info info;

		स_रखो(&info, 0, माप(काष्ठा i2c_board_info));
		info.addr = apanel_addr;
		strlcpy(info.type, "fujitsu_apanel", I2C_NAME_SIZE);
		i2c_new_client_device(&priv->adapter, &info);
	पूर्ण

	अगर (dmi_name_in_venकरोrs("FUJITSU"))
		dmi_walk(dmi_check_onboard_devices, &priv->adapter);

	अगर (is_dell_प्रणाली_with_lis3lv02d())
		रेजिस्टर_dell_lis3lv02d_i2c_device(priv);

	/* Instantiate SPD EEPROMs unless the SMBus is multiplexed */
#अगर IS_ENABLED(CONFIG_I2C_MUX_GPIO)
	अगर (!priv->mux_drvdata)
#पूर्ण_अगर
		i2c_रेजिस्टर_spd(&priv->adapter);
पूर्ण
#अन्यथा
अटल व्योम __init input_apanel_init(व्योम) अणुपूर्ण
अटल व्योम i801_probe_optional_slaves(काष्ठा i801_priv *priv) अणुपूर्ण
#पूर्ण_अगर	/* CONFIG_X86 && CONFIG_DMI */

#अगर IS_ENABLED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
अटल काष्ठा i801_mux_config i801_mux_config_asus_z8_d12 = अणु
	.gpio_chip = "gpio_ich",
	.values = अणु 0x02, 0x03 पूर्ण,
	.n_values = 2,
	.classes = अणु I2C_CLASS_SPD, I2C_CLASS_SPD पूर्ण,
	.gpios = अणु 52, 53 पूर्ण,
	.n_gpios = 2,
पूर्ण;

अटल काष्ठा i801_mux_config i801_mux_config_asus_z8_d18 = अणु
	.gpio_chip = "gpio_ich",
	.values = अणु 0x02, 0x03, 0x01 पूर्ण,
	.n_values = 3,
	.classes = अणु I2C_CLASS_SPD, I2C_CLASS_SPD, I2C_CLASS_SPD पूर्ण,
	.gpios = अणु 52, 53 पूर्ण,
	.n_gpios = 2,
पूर्ण;

अटल स्थिर काष्ठा dmi_प्रणाली_id mux_dmi_table[] = अणु
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8NA-D6(C)"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8P(N)E-D12(X)"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8NH-D12"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8PH-D12/IFB"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8NR-D12"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8P(N)H-D12"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8PG-D18"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d18,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8PE-D18"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d18,
	पूर्ण,
	अणु
		.matches = अणु
			DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
			DMI_MATCH(DMI_BOARD_NAME, "Z8PS-D12"),
		पूर्ण,
		.driver_data = &i801_mux_config_asus_z8_d12,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Setup multiplexing अगर needed */
अटल पूर्णांक i801_add_mux(काष्ठा i801_priv *priv)
अणु
	काष्ठा device *dev = &priv->adapter.dev;
	स्थिर काष्ठा i801_mux_config *mux_config;
	काष्ठा i2c_mux_gpio_platक्रमm_data gpio_data;
	काष्ठा gpiod_lookup_table *lookup;
	पूर्णांक i;

	अगर (!priv->mux_drvdata)
		वापस 0;
	mux_config = priv->mux_drvdata;

	/* Prepare the platक्रमm data */
	स_रखो(&gpio_data, 0, माप(काष्ठा i2c_mux_gpio_platक्रमm_data));
	gpio_data.parent = priv->adapter.nr;
	gpio_data.values = mux_config->values;
	gpio_data.n_values = mux_config->n_values;
	gpio_data.classes = mux_config->classes;
	gpio_data.idle = I2C_MUX_GPIO_NO_IDLE;

	/* Register GPIO descriptor lookup table */
	lookup = devm_kzalloc(dev,
			      काष्ठा_size(lookup, table, mux_config->n_gpios + 1),
			      GFP_KERNEL);
	अगर (!lookup)
		वापस -ENOMEM;
	lookup->dev_id = "i2c-mux-gpio";
	क्रम (i = 0; i < mux_config->n_gpios; i++) अणु
		lookup->table[i] = (काष्ठा gpiod_lookup)
			GPIO_LOOKUP(mux_config->gpio_chip,
				    mux_config->gpios[i], "mux", 0);
	पूर्ण
	gpiod_add_lookup_table(lookup);
	priv->lookup = lookup;

	/*
	 * Register the mux device, we use PLATFORM_DEVID_NONE here
	 * because since we are referring to the GPIO chip by name we are
	 * anyways in deep trouble अगर there is more than one of these
	 * devices, and there should likely only be one platक्रमm controller
	 * hub.
	 */
	priv->mux_pdev = platक्रमm_device_रेजिस्टर_data(dev, "i2c-mux-gpio",
				PLATFORM_DEVID_NONE, &gpio_data,
				माप(काष्ठा i2c_mux_gpio_platक्रमm_data));
	अगर (IS_ERR(priv->mux_pdev)) अणु
		gpiod_हटाओ_lookup_table(lookup);
		dev_err(dev, "Failed to register i2c-mux-gpio device\n");
	पूर्ण

	वापस PTR_ERR_OR_ZERO(priv->mux_pdev);
पूर्ण

अटल व्योम i801_del_mux(काष्ठा i801_priv *priv)
अणु
	platक्रमm_device_unरेजिस्टर(priv->mux_pdev);
	gpiod_हटाओ_lookup_table(priv->lookup);
पूर्ण

अटल अचिन्हित पूर्णांक i801_get_adapter_class(काष्ठा i801_priv *priv)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *id;
	स्थिर काष्ठा i801_mux_config *mux_config;
	अचिन्हित पूर्णांक class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	पूर्णांक i;

	id = dmi_first_match(mux_dmi_table);
	अगर (id) अणु
		/* Remove branch classes from trunk */
		mux_config = id->driver_data;
		क्रम (i = 0; i < mux_config->n_values; i++)
			class &= ~mux_config->classes[i];

		/* Remember क्रम later */
		priv->mux_drvdata = mux_config;
	पूर्ण

	वापस class;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक i801_add_mux(काष्ठा i801_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम i801_del_mux(काष्ठा i801_priv *priv) अणु पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक i801_get_adapter_class(काष्ठा i801_priv *priv)
अणु
	वापस I2C_CLASS_HWMON | I2C_CLASS_SPD;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा itco_wdt_platक्रमm_data spt_tco_platक्रमm_data = अणु
	.name = "Intel PCH",
	.version = 4,
पूर्ण;

अटल DEFINE_SPINLOCK(p2sb_spinlock);

अटल काष्ठा platक्रमm_device *
i801_add_tco_spt(काष्ठा i801_priv *priv, काष्ठा pci_dev *pci_dev,
		 काष्ठा resource *tco_res)
अणु
	काष्ठा resource *res;
	अचिन्हित पूर्णांक devfn;
	u64 base64_addr;
	u32 base_addr;
	u8 hidden;

	/*
	 * We must access the NO_REBOOT bit over the Primary to Sideband
	 * bridge (P2SB). The BIOS prevents the P2SB device from being
	 * क्रमागतerated by the PCI subप्रणाली, so we need to unhide/hide it
	 * to lookup the P2SB BAR.
	 */
	spin_lock(&p2sb_spinlock);

	devfn = PCI_DEVFN(PCI_SLOT(pci_dev->devfn), 1);

	/* Unhide the P2SB device, अगर it is hidden */
	pci_bus_पढ़ो_config_byte(pci_dev->bus, devfn, 0xe1, &hidden);
	अगर (hidden)
		pci_bus_ग_लिखो_config_byte(pci_dev->bus, devfn, 0xe1, 0x0);

	pci_bus_पढ़ो_config_dword(pci_dev->bus, devfn, SBREG_BAR, &base_addr);
	base64_addr = base_addr & 0xfffffff0;

	pci_bus_पढ़ो_config_dword(pci_dev->bus, devfn, SBREG_BAR + 0x4, &base_addr);
	base64_addr |= (u64)base_addr << 32;

	/* Hide the P2SB device, अगर it was hidden beक्रमe */
	अगर (hidden)
		pci_bus_ग_लिखो_config_byte(pci_dev->bus, devfn, 0xe1, hidden);
	spin_unlock(&p2sb_spinlock);

	res = &tco_res[1];
	अगर (pci_dev->device == PCI_DEVICE_ID_INTEL_DNV_SMBUS)
		res->start = (resource_माप_प्रकार)base64_addr + SBREG_SMBCTRL_DNV;
	अन्यथा
		res->start = (resource_माप_प्रकार)base64_addr + SBREG_SMBCTRL;

	res->end = res->start + 3;
	res->flags = IORESOURCE_MEM;

	वापस platक्रमm_device_रेजिस्टर_resndata(&pci_dev->dev, "iTCO_wdt", -1,
					tco_res, 2, &spt_tco_platक्रमm_data,
					माप(spt_tco_platक्रमm_data));
पूर्ण

अटल स्थिर काष्ठा itco_wdt_platक्रमm_data cnl_tco_platक्रमm_data = अणु
	.name = "Intel PCH",
	.version = 6,
पूर्ण;

अटल काष्ठा platक्रमm_device *
i801_add_tco_cnl(काष्ठा i801_priv *priv, काष्ठा pci_dev *pci_dev,
		 काष्ठा resource *tco_res)
अणु
	वापस platक्रमm_device_रेजिस्टर_resndata(&pci_dev->dev,
			"iTCO_wdt", -1, tco_res, 1, &cnl_tco_platक्रमm_data,
			माप(cnl_tco_platक्रमm_data));
पूर्ण

अटल व्योम i801_add_tco(काष्ठा i801_priv *priv)
अणु
	काष्ठा pci_dev *pci_dev = priv->pci_dev;
	काष्ठा resource tco_res[2], *res;
	u32 tco_base, tco_ctl;

	/* If we have ACPI based watchकरोg use that instead */
	अगर (acpi_has_watchकरोg())
		वापस;

	अगर (!(priv->features & (FEATURE_TCO_SPT | FEATURE_TCO_CNL)))
		वापस;

	pci_पढ़ो_config_dword(pci_dev, TCOBASE, &tco_base);
	pci_पढ़ो_config_dword(pci_dev, TCOCTL, &tco_ctl);
	अगर (!(tco_ctl & TCOCTL_EN))
		वापस;

	स_रखो(tco_res, 0, माप(tco_res));
	/*
	 * Always populate the मुख्य iTCO IO resource here. The second entry
	 * क्रम NO_REBOOT MMIO is filled by the SPT specअगरic function.
	 */
	res = &tco_res[0];
	res->start = tco_base & ~1;
	res->end = res->start + 32 - 1;
	res->flags = IORESOURCE_IO;

	अगर (priv->features & FEATURE_TCO_CNL)
		priv->tco_pdev = i801_add_tco_cnl(priv, pci_dev, tco_res);
	अन्यथा
		priv->tco_pdev = i801_add_tco_spt(priv, pci_dev, tco_res);

	अगर (IS_ERR(priv->tco_pdev))
		dev_warn(&pci_dev->dev, "failed to create iTCO device\n");
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool i801_acpi_is_smbus_ioport(स्थिर काष्ठा i801_priv *priv,
				      acpi_physical_address address)
अणु
	वापस address >= priv->smba &&
	       address <= pci_resource_end(priv->pci_dev, SMBBAR);
पूर्ण

अटल acpi_status
i801_acpi_io_handler(u32 function, acpi_physical_address address, u32 bits,
		     u64 *value, व्योम *handler_context, व्योम *region_context)
अणु
	काष्ठा i801_priv *priv = handler_context;
	काष्ठा pci_dev *pdev = priv->pci_dev;
	acpi_status status;

	/*
	 * Once BIOS AML code touches the OpRegion we warn and inhibit any
	 * further access from the driver itself. This device is now owned
	 * by the प्रणाली firmware.
	 */
	mutex_lock(&priv->acpi_lock);

	अगर (!priv->acpi_reserved && i801_acpi_is_smbus_ioport(priv, address)) अणु
		priv->acpi_reserved = true;

		dev_warn(&pdev->dev, "BIOS is accessing SMBus registers\n");
		dev_warn(&pdev->dev, "Driver SMBus register access inhibited\n");

		/*
		 * BIOS is accessing the host controller so prevent it from
		 * suspending स्वतःmatically from now on.
		 */
		pm_runसमय_get_sync(&pdev->dev);
	पूर्ण

	अगर ((function & ACPI_IO_MASK) == ACPI_READ)
		status = acpi_os_पढ़ो_port(address, (u32 *)value, bits);
	अन्यथा
		status = acpi_os_ग_लिखो_port(address, (u32)*value, bits);

	mutex_unlock(&priv->acpi_lock);

	वापस status;
पूर्ण

अटल पूर्णांक i801_acpi_probe(काष्ठा i801_priv *priv)
अणु
	काष्ठा acpi_device *adev;
	acpi_status status;

	adev = ACPI_COMPANION(&priv->pci_dev->dev);
	अगर (adev) अणु
		status = acpi_install_address_space_handler(adev->handle,
				ACPI_ADR_SPACE_SYSTEM_IO, i801_acpi_io_handler,
				शून्य, priv);
		अगर (ACPI_SUCCESS(status))
			वापस 0;
	पूर्ण

	वापस acpi_check_resource_conflict(&priv->pci_dev->resource[SMBBAR]);
पूर्ण

अटल व्योम i801_acpi_हटाओ(काष्ठा i801_priv *priv)
अणु
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(&priv->pci_dev->dev);
	अगर (!adev)
		वापस;

	acpi_हटाओ_address_space_handler(adev->handle,
		ACPI_ADR_SPACE_SYSTEM_IO, i801_acpi_io_handler);

	mutex_lock(&priv->acpi_lock);
	अगर (priv->acpi_reserved)
		pm_runसमय_put(&priv->pci_dev->dev);
	mutex_unlock(&priv->acpi_lock);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक i801_acpi_probe(काष्ठा i801_priv *priv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम i801_acpi_हटाओ(काष्ठा i801_priv *priv) अणु पूर्ण
#पूर्ण_अगर

अटल अचिन्हित अक्षर i801_setup_hstcfg(काष्ठा i801_priv *priv)
अणु
	अचिन्हित अक्षर hstcfg = priv->original_hstcfg;

	hstcfg &= ~SMBHSTCFG_I2C_EN;	/* SMBus timing */
	hstcfg |= SMBHSTCFG_HST_EN;
	pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG, hstcfg);
	वापस hstcfg;
पूर्ण

अटल पूर्णांक i801_probe(काष्ठा pci_dev *dev, स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित अक्षर temp;
	पूर्णांक err, i;
	काष्ठा i801_priv *priv;

	priv = devm_kzalloc(&dev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_adapdata(&priv->adapter, priv);
	priv->adapter.owner = THIS_MODULE;
	priv->adapter.class = i801_get_adapter_class(priv);
	priv->adapter.algo = &smbus_algorithm;
	priv->adapter.dev.parent = &dev->dev;
	ACPI_COMPANION_SET(&priv->adapter.dev, ACPI_COMPANION(&dev->dev));
	priv->adapter.retries = 3;
	mutex_init(&priv->acpi_lock);

	priv->pci_dev = dev;
	चयन (dev->device) अणु
	हाल PCI_DEVICE_ID_INTEL_SUNRISEPOINT_H_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_SUNRISEPOINT_LP_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_LEWISBURG_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_LEWISBURG_SSKU_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_DNV_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_KABYLAKE_PCH_H_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_COMETLAKE_V_SMBUS:
		priv->features |= FEATURE_BLOCK_PROC;
		priv->features |= FEATURE_I2C_BLOCK_READ;
		priv->features |= FEATURE_IRQ;
		priv->features |= FEATURE_SMBUS_PEC;
		priv->features |= FEATURE_BLOCK_BUFFER;
		priv->features |= FEATURE_TCO_SPT;
		priv->features |= FEATURE_HOST_NOTIFY;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_CANNONLAKE_H_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_CANNONLAKE_LP_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_CDF_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_ICELAKE_LP_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_COMETLAKE_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_COMETLAKE_H_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_ELKHART_LAKE_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_TIGERLAKE_LP_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_TIGERLAKE_H_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_JASPER_LAKE_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_EBG_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_ALDER_LAKE_S_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_ALDER_LAKE_P_SMBUS:
	हाल PCI_DEVICE_ID_INTEL_ALDER_LAKE_M_SMBUS:
		priv->features |= FEATURE_BLOCK_PROC;
		priv->features |= FEATURE_I2C_BLOCK_READ;
		priv->features |= FEATURE_IRQ;
		priv->features |= FEATURE_SMBUS_PEC;
		priv->features |= FEATURE_BLOCK_BUFFER;
		priv->features |= FEATURE_TCO_CNL;
		priv->features |= FEATURE_HOST_NOTIFY;
		अवरोध;

	हाल PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF0:
	हाल PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF1:
	हाल PCI_DEVICE_ID_INTEL_PATSBURG_SMBUS_IDF2:
	हाल PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS0:
	हाल PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS1:
	हाल PCI_DEVICE_ID_INTEL_WELLSBURG_SMBUS_MS2:
		priv->features |= FEATURE_IDF;
		fallthrough;
	शेष:
		priv->features |= FEATURE_BLOCK_PROC;
		priv->features |= FEATURE_I2C_BLOCK_READ;
		priv->features |= FEATURE_IRQ;
		fallthrough;
	हाल PCI_DEVICE_ID_INTEL_82801DB_3:
		priv->features |= FEATURE_SMBUS_PEC;
		priv->features |= FEATURE_BLOCK_BUFFER;
		fallthrough;
	हाल PCI_DEVICE_ID_INTEL_82801CA_3:
		priv->features |= FEATURE_HOST_NOTIFY;
		fallthrough;
	हाल PCI_DEVICE_ID_INTEL_82801BA_2:
	हाल PCI_DEVICE_ID_INTEL_82801AB_3:
	हाल PCI_DEVICE_ID_INTEL_82801AA_3:
		अवरोध;
	पूर्ण

	/* Disable features on user request */
	क्रम (i = 0; i < ARRAY_SIZE(i801_feature_names); i++) अणु
		अगर (priv->features & disable_features & (1 << i))
			dev_notice(&dev->dev, "%s disabled by user\n",
				   i801_feature_names[i]);
	पूर्ण
	priv->features &= ~disable_features;

	err = pcim_enable_device(dev);
	अगर (err) अणु
		dev_err(&dev->dev, "Failed to enable SMBus PCI device (%d)\n",
			err);
		वापस err;
	पूर्ण
	pcim_pin_device(dev);

	/* Determine the address of the SMBus area */
	priv->smba = pci_resource_start(dev, SMBBAR);
	अगर (!priv->smba) अणु
		dev_err(&dev->dev,
			"SMBus base address uninitialized, upgrade BIOS\n");
		वापस -ENODEV;
	पूर्ण

	अगर (i801_acpi_probe(priv))
		वापस -ENODEV;

	err = pcim_iomap_regions(dev, 1 << SMBBAR,
				 dev_driver_string(&dev->dev));
	अगर (err) अणु
		dev_err(&dev->dev,
			"Failed to request SMBus region 0x%lx-0x%Lx\n",
			priv->smba,
			(अचिन्हित दीर्घ दीर्घ)pci_resource_end(dev, SMBBAR));
		i801_acpi_हटाओ(priv);
		वापस err;
	पूर्ण

	pci_पढ़ो_config_byte(priv->pci_dev, SMBHSTCFG, &priv->original_hstcfg);
	temp = i801_setup_hstcfg(priv);
	अगर (!(priv->original_hstcfg & SMBHSTCFG_HST_EN))
		dev_info(&dev->dev, "Enabling SMBus device\n");

	अगर (temp & SMBHSTCFG_SMB_SMI_EN) अणु
		dev_dbg(&dev->dev, "SMBus using interrupt SMI#\n");
		/* Disable SMBus पूर्णांकerrupt feature अगर SMBus using SMI# */
		priv->features &= ~FEATURE_IRQ;
	पूर्ण
	अगर (temp & SMBHSTCFG_SPD_WD)
		dev_info(&dev->dev, "SPD Write Disable is set\n");

	/* Clear special mode bits */
	अगर (priv->features & (FEATURE_SMBUS_PEC | FEATURE_BLOCK_BUFFER))
		outb_p(inb_p(SMBAUXCTL(priv)) &
		       ~(SMBAUXCTL_CRC | SMBAUXCTL_E32B), SMBAUXCTL(priv));

	/* Remember original Host Notअगरy setting */
	अगर (priv->features & FEATURE_HOST_NOTIFY)
		priv->original_slvcmd = inb_p(SMBSLVCMD(priv));

	/* Default समयout in पूर्णांकerrupt mode: 200 ms */
	priv->adapter.समयout = HZ / 5;

	अगर (dev->irq == IRQ_NOTCONNECTED)
		priv->features &= ~FEATURE_IRQ;

	अगर (priv->features & FEATURE_IRQ) अणु
		u16 pcictl, pcists;

		/* Complain अगर an पूर्णांकerrupt is alपढ़ोy pending */
		pci_पढ़ो_config_word(priv->pci_dev, SMBPCISTS, &pcists);
		अगर (pcists & SMBPCISTS_INTS)
			dev_warn(&dev->dev, "An interrupt is pending!\n");

		/* Check अगर पूर्णांकerrupts have been disabled */
		pci_पढ़ो_config_word(priv->pci_dev, SMBPCICTL, &pcictl);
		अगर (pcictl & SMBPCICTL_INTDIS) अणु
			dev_info(&dev->dev, "Interrupts are disabled\n");
			priv->features &= ~FEATURE_IRQ;
		पूर्ण
	पूर्ण

	अगर (priv->features & FEATURE_IRQ) अणु
		init_रुकोqueue_head(&priv->रुकोq);

		err = devm_request_irq(&dev->dev, dev->irq, i801_isr,
				       IRQF_SHARED,
				       dev_driver_string(&dev->dev), priv);
		अगर (err) अणु
			dev_err(&dev->dev, "Failed to allocate irq %d: %d\n",
				dev->irq, err);
			priv->features &= ~FEATURE_IRQ;
		पूर्ण
	पूर्ण
	dev_info(&dev->dev, "SMBus using %s\n",
		 priv->features & FEATURE_IRQ ? "PCI interrupt" : "polling");

	i801_add_tco(priv);

	snम_लिखो(priv->adapter.name, माप(priv->adapter.name),
		"SMBus I801 adapter at %04lx", priv->smba);
	err = i2c_add_adapter(&priv->adapter);
	अगर (err) अणु
		i801_acpi_हटाओ(priv);
		वापस err;
	पूर्ण

	i801_enable_host_notअगरy(&priv->adapter);

	i801_probe_optional_slaves(priv);
	/* We ignore errors - multiplexing is optional */
	i801_add_mux(priv);

	pci_set_drvdata(dev, priv);

	dev_pm_set_driver_flags(&dev->dev, DPM_FLAG_NO_सूचीECT_COMPLETE);
	pm_runसमय_set_स्वतःsuspend_delay(&dev->dev, 1000);
	pm_runसमय_use_स्वतःsuspend(&dev->dev);
	pm_runसमय_put_स्वतःsuspend(&dev->dev);
	pm_runसमय_allow(&dev->dev);

	वापस 0;
पूर्ण

अटल व्योम i801_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा i801_priv *priv = pci_get_drvdata(dev);

	pm_runसमय_क्रमbid(&dev->dev);
	pm_runसमय_get_noresume(&dev->dev);

	i801_disable_host_notअगरy(priv);
	i801_del_mux(priv);
	i2c_del_adapter(&priv->adapter);
	i801_acpi_हटाओ(priv);
	pci_ग_लिखो_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);

	platक्रमm_device_unरेजिस्टर(priv->tco_pdev);

	/*
	 * करो not call pci_disable_device(dev) since it can cause hard hangs on
	 * some प्रणालीs during घातer-off (eg. Fujitsu-Siemens Lअगरebook E8010)
	 */
पूर्ण

अटल व्योम i801_shutकरोwn(काष्ठा pci_dev *dev)
अणु
	काष्ठा i801_priv *priv = pci_get_drvdata(dev);

	/* Restore config रेजिस्टरs to aव्योम hard hang on some प्रणालीs */
	i801_disable_host_notअगरy(priv);
	pci_ग_लिखो_config_byte(dev, SMBHSTCFG, priv->original_hstcfg);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक i801_suspend(काष्ठा device *dev)
अणु
	काष्ठा i801_priv *priv = dev_get_drvdata(dev);

	pci_ग_लिखो_config_byte(priv->pci_dev, SMBHSTCFG, priv->original_hstcfg);
	वापस 0;
पूर्ण

अटल पूर्णांक i801_resume(काष्ठा device *dev)
अणु
	काष्ठा i801_priv *priv = dev_get_drvdata(dev);

	i801_setup_hstcfg(priv);
	i801_enable_host_notअगरy(&priv->adapter);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(i801_pm_ops, i801_suspend, i801_resume);

अटल काष्ठा pci_driver i801_driver = अणु
	.name		= "i801_smbus",
	.id_table	= i801_ids,
	.probe		= i801_probe,
	.हटाओ		= i801_हटाओ,
	.shutकरोwn	= i801_shutकरोwn,
	.driver		= अणु
		.pm	= &i801_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init i2c_i801_init(व्योम)
अणु
	अगर (dmi_name_in_venकरोrs("FUJITSU"))
		input_apanel_init();
	वापस pci_रेजिस्टर_driver(&i801_driver);
पूर्ण

अटल व्योम __निकास i2c_i801_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&i801_driver);
पूर्ण

MODULE_AUTHOR("Mark D. Studebaker <mdsxyz123@yahoo.com>");
MODULE_AUTHOR("Jean Delvare <jdelvare@suse.de>");
MODULE_DESCRIPTION("I801 SMBus driver");
MODULE_LICENSE("GPL");

module_init(i2c_i801_init);
module_निकास(i2c_i801_निकास);
