<शैली गुरु>
/******************************************************************* 
 *
 * Copyright (c) 2000 ATecoM GmbH 
 *
 * The author may be reached at ecd@atecom.com.
 *
 * This program is मुक्त software; you can redistribute  it and/or modअगरy it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 * THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR   IMPLIED
 * WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   सूचीECT,  INसूचीECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 * USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *******************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/poison.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/kernel.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/aपंचांगdev.h>
#समावेश <linux/aपंचांग.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/रुको.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित CONFIG_ATM_IDT77252_USE_SUNI
#समावेश "suni.h"
#पूर्ण_अगर /* CONFIG_ATM_IDT77252_USE_SUNI */


#समावेश "idt77252.h"
#समावेश "idt77252_tables.h"

अटल अचिन्हित पूर्णांक vpibits = 1;


#घोषणा ATM_IDT77252_SEND_IDLE 1


/*
 * Debug HACKs.
 */
#घोषणा DEBUG_MODULE 1
#अघोषित HAVE_EEPROM	/* करोes not work, yet. */

#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
अटल अचिन्हित दीर्घ debug = DBG_GENERAL;
#पूर्ण_अगर


#घोषणा SAR_RX_DELAY	(SAR_CFG_RXINT_NODELAY)


/*
 * SCQ Handling.
 */
अटल काष्ठा scq_info *alloc_scq(काष्ठा idt77252_dev *, पूर्णांक);
अटल व्योम मुक्त_scq(काष्ठा idt77252_dev *, काष्ठा scq_info *);
अटल पूर्णांक queue_skb(काष्ठा idt77252_dev *, काष्ठा vc_map *,
		     काष्ठा sk_buff *, पूर्णांक oam);
अटल व्योम drain_scq(काष्ठा idt77252_dev *, काष्ठा vc_map *);
अटल अचिन्हित दीर्घ get_मुक्त_scd(काष्ठा idt77252_dev *, काष्ठा vc_map *);
अटल व्योम fill_scd(काष्ठा idt77252_dev *, काष्ठा scq_info *, पूर्णांक);

/*
 * FBQ Handling.
 */
अटल पूर्णांक push_rx_skb(काष्ठा idt77252_dev *,
		       काष्ठा sk_buff *, पूर्णांक queue);
अटल व्योम recycle_rx_skb(काष्ठा idt77252_dev *, काष्ठा sk_buff *);
अटल व्योम flush_rx_pool(काष्ठा idt77252_dev *, काष्ठा rx_pool *);
अटल व्योम recycle_rx_pool_skb(काष्ठा idt77252_dev *,
				काष्ठा rx_pool *);
अटल व्योम add_rx_skb(काष्ठा idt77252_dev *, पूर्णांक queue,
		       अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक count);

/*
 * RSQ Handling.
 */
अटल पूर्णांक init_rsq(काष्ठा idt77252_dev *);
अटल व्योम deinit_rsq(काष्ठा idt77252_dev *);
अटल व्योम idt77252_rx(काष्ठा idt77252_dev *);

/*
 * TSQ handling.
 */
अटल पूर्णांक init_tsq(काष्ठा idt77252_dev *);
अटल व्योम deinit_tsq(काष्ठा idt77252_dev *);
अटल व्योम idt77252_tx(काष्ठा idt77252_dev *);


/*
 * ATM Interface.
 */
अटल व्योम idt77252_dev_बंद(काष्ठा aपंचांग_dev *dev);
अटल पूर्णांक idt77252_खोलो(काष्ठा aपंचांग_vcc *vcc);
अटल व्योम idt77252_बंद(काष्ठा aपंचांग_vcc *vcc);
अटल पूर्णांक idt77252_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb);
अटल पूर्णांक idt77252_send_oam(काष्ठा aपंचांग_vcc *vcc, व्योम *cell,
			     पूर्णांक flags);
अटल व्योम idt77252_phy_put(काष्ठा aपंचांग_dev *dev, अचिन्हित अक्षर value,
			     अचिन्हित दीर्घ addr);
अटल अचिन्हित अक्षर idt77252_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr);
अटल पूर्णांक idt77252_change_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos,
			       पूर्णांक flags);
अटल पूर्णांक idt77252_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t * pos,
			      अक्षर *page);
अटल व्योम idt77252_softपूर्णांक(काष्ठा work_काष्ठा *work);


अटल स्थिर काष्ठा aपंचांगdev_ops idt77252_ops =
अणु
	.dev_बंद	= idt77252_dev_बंद,
	.खोलो		= idt77252_खोलो,
	.बंद		= idt77252_बंद,
	.send		= idt77252_send,
	.send_oam	= idt77252_send_oam,
	.phy_put	= idt77252_phy_put,
	.phy_get	= idt77252_phy_get,
	.change_qos	= idt77252_change_qos,
	.proc_पढ़ो	= idt77252_proc_पढ़ो,
	.owner		= THIS_MODULE
पूर्ण;

अटल काष्ठा idt77252_dev *idt77252_chain = शून्य;
अटल अचिन्हित पूर्णांक idt77252_sram_ग_लिखो_errors = 0;

/*****************************************************************************/
/*                                                                           */
/* I/O and Utility Bus                                                       */
/*                                                                           */
/*****************************************************************************/

अटल व्योम
रुकोक्रम_idle(काष्ठा idt77252_dev *card)
अणु
	u32 stat;

	stat = पढ़ोl(SAR_REG_STAT);
	जबतक (stat & SAR_STAT_CMDBZ)
		stat = पढ़ोl(SAR_REG_STAT);
पूर्ण

अटल u32
पढ़ो_sram(काष्ठा idt77252_dev *card, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags;
	u32 value;

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl(SAR_CMD_READ_SRAM | (addr << 2), SAR_REG_CMD);
	रुकोक्रम_idle(card);
	value = पढ़ोl(SAR_REG_DR0);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
	वापस value;
पूर्ण

अटल व्योम
ग_लिखो_sram(काष्ठा idt77252_dev *card, अचिन्हित दीर्घ addr, u32 value)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((idt77252_sram_ग_लिखो_errors == 0) &&
	    (((addr > card->tst[0] + card->tst_size - 2) &&
	      (addr < card->tst[0] + card->tst_size)) ||
	     ((addr > card->tst[1] + card->tst_size - 2) &&
	      (addr < card->tst[1] + card->tst_size)))) अणु
		prपूर्णांकk("%s: ERROR: TST JMP section at %08lx written: %08x\n",
		       card->name, addr, value);
	पूर्ण

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl(value, SAR_REG_DR0);
	ग_लिखोl(SAR_CMD_WRITE_SRAM | (addr << 2), SAR_REG_CMD);
	रुकोक्रम_idle(card);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
पूर्ण

अटल u8
पढ़ो_utility(व्योम *dev, अचिन्हित दीर्घ ubus_addr)
अणु
	काष्ठा idt77252_dev *card = dev;
	अचिन्हित दीर्घ flags;
	u8 value;

	अगर (!card) अणु
		prपूर्णांकk("Error: No such device.\n");
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl(SAR_CMD_READ_UTILITY + ubus_addr, SAR_REG_CMD);
	रुकोक्रम_idle(card);
	value = पढ़ोl(SAR_REG_DR0);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
	वापस value;
पूर्ण

अटल व्योम
ग_लिखो_utility(व्योम *dev, अचिन्हित दीर्घ ubus_addr, u8 value)
अणु
	काष्ठा idt77252_dev *card = dev;
	अचिन्हित दीर्घ flags;

	अगर (!card) अणु
		prपूर्णांकk("Error: No such device.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl((u32) value, SAR_REG_DR0);
	ग_लिखोl(SAR_CMD_WRITE_UTILITY + ubus_addr, SAR_REG_CMD);
	रुकोक्रम_idle(card);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
पूर्ण

#अगर_घोषित HAVE_EEPROM
अटल u32 rdsrtab[] =
अणु
	SAR_GP_EECS | SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO,	/* 1 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO	/* 1 */
पूर्ण;

अटल u32 wrentab[] =
अणु
	SAR_GP_EECS | SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO,	/* 1 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO,	/* 1 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK			/* 0 */
पूर्ण;

अटल u32 rdtab[] =
अणु
	SAR_GP_EECS | SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO,	/* 1 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO	/* 1 */
पूर्ण;

अटल u32 wrtab[] =
अणु
	SAR_GP_EECS | SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	0,
	SAR_GP_EESCLK,			/* 0 */
	SAR_GP_EEDO,
	SAR_GP_EESCLK | SAR_GP_EEDO,	/* 1 */
	0,
	SAR_GP_EESCLK			/* 0 */
पूर्ण;

अटल u32 clktab[] =
अणु
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0,
	SAR_GP_EESCLK,
	0
पूर्ण;

अटल u32
idt77252_पढ़ो_gp(काष्ठा idt77252_dev *card)
अणु
	u32 gp;

	gp = पढ़ोl(SAR_REG_GP);
#अगर 0
	prपूर्णांकk("RD: %s\n", gp & SAR_GP_EEDI ? "1" : "0");
#पूर्ण_अगर
	वापस gp;
पूर्ण

अटल व्योम
idt77252_ग_लिखो_gp(काष्ठा idt77252_dev *card, u32 value)
अणु
	अचिन्हित दीर्घ flags;

#अगर 0
	prपूर्णांकk("WR: %s %s %s\n", value & SAR_GP_EECS ? "   " : "/CS",
	       value & SAR_GP_EESCLK ? "HIGH" : "LOW ",
	       value & SAR_GP_EEDO   ? "1" : "0");
#पूर्ण_अगर

	spin_lock_irqsave(&card->cmd_lock, flags);
	रुकोक्रम_idle(card);
	ग_लिखोl(value, SAR_REG_GP);
	spin_unlock_irqrestore(&card->cmd_lock, flags);
पूर्ण

अटल u8
idt77252_eeprom_पढ़ो_status(काष्ठा idt77252_dev *card)
अणु
	u8 byte;
	u32 gp;
	पूर्णांक i, j;

	gp = idt77252_पढ़ो_gp(card) & ~(SAR_GP_EESCLK|SAR_GP_EECS|SAR_GP_EEDO);

	क्रम (i = 0; i < ARRAY_SIZE(rdsrtab); i++) अणु
		idt77252_ग_लिखो_gp(card, gp | rdsrtab[i]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	byte = 0;
	क्रम (i = 0, j = 0; i < 8; i++) अणु
		byte <<= 1;

		idt77252_ग_लिखो_gp(card, gp | clktab[j++]);
		udelay(5);

		byte |= idt77252_पढ़ो_gp(card) & SAR_GP_EEDI ? 1 : 0;

		idt77252_ग_लिखो_gp(card, gp | clktab[j++]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	वापस byte;
पूर्ण

अटल u8
idt77252_eeprom_पढ़ो_byte(काष्ठा idt77252_dev *card, u8 offset)
अणु
	u8 byte;
	u32 gp;
	पूर्णांक i, j;

	gp = idt77252_पढ़ो_gp(card) & ~(SAR_GP_EESCLK|SAR_GP_EECS|SAR_GP_EEDO);

	क्रम (i = 0; i < ARRAY_SIZE(rdtab); i++) अणु
		idt77252_ग_लिखो_gp(card, gp | rdtab[i]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	क्रम (i = 0, j = 0; i < 8; i++) अणु
		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(offset & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(offset & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		offset >>= 1;
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	byte = 0;
	क्रम (i = 0, j = 0; i < 8; i++) अणु
		byte <<= 1;

		idt77252_ग_लिखो_gp(card, gp | clktab[j++]);
		udelay(5);

		byte |= idt77252_पढ़ो_gp(card) & SAR_GP_EEDI ? 1 : 0;

		idt77252_ग_लिखो_gp(card, gp | clktab[j++]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	वापस byte;
पूर्ण

अटल व्योम
idt77252_eeprom_ग_लिखो_byte(काष्ठा idt77252_dev *card, u8 offset, u8 data)
अणु
	u32 gp;
	पूर्णांक i, j;

	gp = idt77252_पढ़ो_gp(card) & ~(SAR_GP_EESCLK|SAR_GP_EECS|SAR_GP_EEDO);

	क्रम (i = 0; i < ARRAY_SIZE(wrentab); i++) अणु
		idt77252_ग_लिखो_gp(card, gp | wrentab[i]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	क्रम (i = 0; i < ARRAY_SIZE(wrtab); i++) अणु
		idt77252_ग_लिखो_gp(card, gp | wrtab[i]);
		udelay(5);
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	क्रम (i = 0, j = 0; i < 8; i++) अणु
		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(offset & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(offset & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		offset >>= 1;
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);

	क्रम (i = 0, j = 0; i < 8; i++) अणु
		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(data & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		idt77252_ग_लिखो_gp(card, gp | clktab[j++] |
					(data & 1 ? SAR_GP_EEDO : 0));
		udelay(5);

		data >>= 1;
	पूर्ण
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);
पूर्ण

अटल व्योम
idt77252_eeprom_init(काष्ठा idt77252_dev *card)
अणु
	u32 gp;

	gp = idt77252_पढ़ो_gp(card) & ~(SAR_GP_EESCLK|SAR_GP_EECS|SAR_GP_EEDO);

	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS | SAR_GP_EESCLK);
	udelay(5);
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS | SAR_GP_EESCLK);
	udelay(5);
	idt77252_ग_लिखो_gp(card, gp | SAR_GP_EECS);
	udelay(5);
पूर्ण
#पूर्ण_अगर /* HAVE_EEPROM */


#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
अटल व्योम
dump_tct(काष्ठा idt77252_dev *card, पूर्णांक index)
अणु
	अचिन्हित दीर्घ tct;
	पूर्णांक i;

	tct = (अचिन्हित दीर्घ) (card->tct_base + index * SAR_SRAM_TCT_SIZE);

	prपूर्णांकk("%s: TCT %x:", card->name, index);
	क्रम (i = 0; i < 8; i++) अणु
		prपूर्णांकk(" %08x", पढ़ो_sram(card, tct + i));
	पूर्ण
	prपूर्णांकk("\n");
पूर्ण

अटल व्योम
idt77252_tx_dump(काष्ठा idt77252_dev *card)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा vc_map *vc;
	पूर्णांक i;

	prपूर्णांकk("%s\n", __func__);
	क्रम (i = 0; i < card->tct_size; i++) अणु
		vc = card->vcs[i];
		अगर (!vc)
			जारी;

		vcc = शून्य;
		अगर (vc->rx_vcc)
			vcc = vc->rx_vcc;
		अन्यथा अगर (vc->tx_vcc)
			vcc = vc->tx_vcc;

		अगर (!vcc)
			जारी;

		prपूर्णांकk("%s: Connection %d:\n", card->name, vc->index);
		dump_tct(card, vc->index);
	पूर्ण
पूर्ण
#पूर्ण_अगर


/*****************************************************************************/
/*                                                                           */
/* SCQ Handling                                                              */
/*                                                                           */
/*****************************************************************************/

अटल पूर्णांक
sb_pool_add(काष्ठा idt77252_dev *card, काष्ठा sk_buff *skb, पूर्णांक queue)
अणु
	काष्ठा sb_pool *pool = &card->sbpool[queue];
	पूर्णांक index;

	index = pool->index;
	जबतक (pool->skb[index]) अणु
		index = (index + 1) & FBQ_MASK;
		अगर (index == pool->index)
			वापस -ENOBUFS;
	पूर्ण

	pool->skb[index] = skb;
	IDT77252_PRV_POOL(skb) = POOL_HANDLE(queue, index);

	pool->index = (index + 1) & FBQ_MASK;
	वापस 0;
पूर्ण

अटल व्योम
sb_pool_हटाओ(काष्ठा idt77252_dev *card, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक queue, index;
	u32 handle;

	handle = IDT77252_PRV_POOL(skb);

	queue = POOL_QUEUE(handle);
	अगर (queue > 3)
		वापस;

	index = POOL_INDEX(handle);
	अगर (index > FBQ_SIZE - 1)
		वापस;

	card->sbpool[queue].skb[index] = शून्य;
पूर्ण

अटल काष्ठा sk_buff *
sb_pool_skb(काष्ठा idt77252_dev *card, u32 handle)
अणु
	अचिन्हित पूर्णांक queue, index;

	queue = POOL_QUEUE(handle);
	अगर (queue > 3)
		वापस शून्य;

	index = POOL_INDEX(handle);
	अगर (index > FBQ_SIZE - 1)
		वापस शून्य;

	वापस card->sbpool[queue].skb[index];
पूर्ण

अटल काष्ठा scq_info *
alloc_scq(काष्ठा idt77252_dev *card, पूर्णांक class)
अणु
	काष्ठा scq_info *scq;

	scq = kzalloc(माप(काष्ठा scq_info), GFP_KERNEL);
	अगर (!scq)
		वापस शून्य;
	scq->base = dma_alloc_coherent(&card->pcidev->dev, SCQ_SIZE,
				       &scq->paddr, GFP_KERNEL);
	अगर (scq->base == शून्य) अणु
		kमुक्त(scq);
		वापस शून्य;
	पूर्ण

	scq->next = scq->base;
	scq->last = scq->base + (SCQ_ENTRIES - 1);
	atomic_set(&scq->used, 0);

	spin_lock_init(&scq->lock);
	spin_lock_init(&scq->skblock);

	skb_queue_head_init(&scq->transmit);
	skb_queue_head_init(&scq->pending);

	TXPRINTK("idt77252: SCQ: base 0x%p, next 0x%p, last 0x%p, paddr %08llx\n",
		 scq->base, scq->next, scq->last, (अचिन्हित दीर्घ दीर्घ)scq->paddr);

	वापस scq;
पूर्ण

अटल व्योम
मुक्त_scq(काष्ठा idt77252_dev *card, काष्ठा scq_info *scq)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांग_vcc *vcc;

	dma_मुक्त_coherent(&card->pcidev->dev, SCQ_SIZE,
			  scq->base, scq->paddr);

	जबतक ((skb = skb_dequeue(&scq->transmit))) अणु
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;
		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb(skb);
	पूर्ण

	जबतक ((skb = skb_dequeue(&scq->pending))) अणु
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;
		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb(skb);
	पूर्ण

	kमुक्त(scq);
पूर्ण


अटल पूर्णांक
push_on_scq(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc, काष्ठा sk_buff *skb)
अणु
	काष्ठा scq_info *scq = vc->scq;
	अचिन्हित दीर्घ flags;
	काष्ठा scqe *tbd;
	पूर्णांक entries;

	TXPRINTK("%s: SCQ: next 0x%p\n", card->name, scq->next);

	atomic_inc(&scq->used);
	entries = atomic_पढ़ो(&scq->used);
	अगर (entries > (SCQ_ENTRIES - 1)) अणु
		atomic_dec(&scq->used);
		जाओ out;
	पूर्ण

	skb_queue_tail(&scq->transmit, skb);

	spin_lock_irqsave(&vc->lock, flags);
	अगर (vc->estimator) अणु
		काष्ठा aपंचांग_vcc *vcc = vc->tx_vcc;
		काष्ठा sock *sk = sk_aपंचांग(vcc);

		vc->estimator->cells += (skb->len + 47) / 48;
		अगर (refcount_पढ़ो(&sk->sk_wmem_alloc) >
		    (sk->sk_sndbuf >> 1)) अणु
			u32 cps = vc->estimator->maxcps;

			vc->estimator->cps = cps;
			vc->estimator->avcps = cps << 5;
			अगर (vc->lacr < vc->init_er) अणु
				vc->lacr = vc->init_er;
				ग_लिखोl(TCMDQ_LACR | (vc->lacr << 16) |
				       vc->index, SAR_REG_TCMDQ);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vc->lock, flags);

	tbd = &IDT77252_PRV_TBD(skb);

	spin_lock_irqsave(&scq->lock, flags);
	scq->next->word_1 = cpu_to_le32(tbd->word_1 |
					SAR_TBD_TSIF | SAR_TBD_GTSI);
	scq->next->word_2 = cpu_to_le32(tbd->word_2);
	scq->next->word_3 = cpu_to_le32(tbd->word_3);
	scq->next->word_4 = cpu_to_le32(tbd->word_4);

	अगर (scq->next == scq->last)
		scq->next = scq->base;
	अन्यथा
		scq->next++;

	ग_लिखो_sram(card, scq->scd,
		   scq->paddr +
		   (u32)((अचिन्हित दीर्घ)scq->next - (अचिन्हित दीर्घ)scq->base));
	spin_unlock_irqrestore(&scq->lock, flags);

	scq->trans_start = jअगरfies;

	अगर (test_and_clear_bit(VCF_IDLE, &vc->flags)) अणु
		ग_लिखोl(TCMDQ_START_LACR | (vc->lacr << 16) | vc->index,
		       SAR_REG_TCMDQ);
	पूर्ण

	TXPRINTK("%d entries in SCQ used (push).\n", atomic_पढ़ो(&scq->used));

	XPRINTK("%s: SCQ (after push %2d) head = 0x%x, next = 0x%p.\n",
		card->name, atomic_पढ़ो(&scq->used),
		पढ़ो_sram(card, scq->scd + 1), scq->next);

	वापस 0;

out:
	अगर (समय_after(jअगरfies, scq->trans_start + HZ)) अणु
		prपूर्णांकk("%s: Error pushing TBD for %d.%d\n",
		       card->name, vc->tx_vcc->vpi, vc->tx_vcc->vci);
#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
		idt77252_tx_dump(card);
#पूर्ण_अगर
		scq->trans_start = jअगरfies;
	पूर्ण

	वापस -ENOBUFS;
पूर्ण


अटल व्योम
drain_scq(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc)
अणु
	काष्ठा scq_info *scq = vc->scq;
	काष्ठा sk_buff *skb;
	काष्ठा aपंचांग_vcc *vcc;

	TXPRINTK("%s: SCQ (before drain %2d) next = 0x%p.\n",
		 card->name, atomic_पढ़ो(&scq->used), scq->next);

	skb = skb_dequeue(&scq->transmit);
	अगर (skb) अणु
		TXPRINTK("%s: freeing skb at %p.\n", card->name, skb);

		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb->len, DMA_TO_DEVICE);

		vcc = ATM_SKB(skb)->vcc;

		अगर (vcc->pop)
			vcc->pop(vcc, skb);
		अन्यथा
			dev_kमुक्त_skb(skb);

		atomic_inc(&vcc->stats->tx);
	पूर्ण

	atomic_dec(&scq->used);

	spin_lock(&scq->skblock);
	जबतक ((skb = skb_dequeue(&scq->pending))) अणु
		अगर (push_on_scq(card, vc, skb)) अणु
			skb_queue_head(&vc->scq->pending, skb);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&scq->skblock);
पूर्ण

अटल पूर्णांक
queue_skb(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
	  काष्ठा sk_buff *skb, पूर्णांक oam)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा scqe *tbd;
	अचिन्हित दीर्घ flags;
	पूर्णांक error;
	पूर्णांक aal;
	u32 word4;

	अगर (skb->len == 0) अणु
		prपूर्णांकk("%s: invalid skb->len (%d)\n", card->name, skb->len);
		वापस -EINVAL;
	पूर्ण

	TXPRINTK("%s: Sending %d bytes of data.\n",
		 card->name, skb->len);

	tbd = &IDT77252_PRV_TBD(skb);
	vcc = ATM_SKB(skb)->vcc;
	word4 = (skb->data[0] << 24) | (skb->data[1] << 16) |
			(skb->data[2] <<  8) | (skb->data[3] <<  0);

	IDT77252_PRV_PADDR(skb) = dma_map_single(&card->pcidev->dev, skb->data,
						 skb->len, DMA_TO_DEVICE);

	error = -EINVAL;

	अगर (oam) अणु
		अगर (skb->len != 52)
			जाओ errout;

		tbd->word_1 = SAR_TBD_OAM | ATM_CELL_PAYLOAD | SAR_TBD_EPDU;
		tbd->word_2 = IDT77252_PRV_PADDR(skb) + 4;
		tbd->word_3 = 0x00000000;
		tbd->word_4 = word4;

		अगर (test_bit(VCF_RSV, &vc->flags))
			vc = card->vcs[0];

		जाओ करोne;
	पूर्ण

	अगर (test_bit(VCF_RSV, &vc->flags)) अणु
		prपूर्णांकk("%s: Trying to transmit on reserved VC\n", card->name);
		जाओ errout;
	पूर्ण

	aal = vcc->qos.aal;

	चयन (aal) अणु
	हाल ATM_AAL0:
	हाल ATM_AAL34:
		अगर (skb->len > 52)
			जाओ errout;

		अगर (aal == ATM_AAL0)
			tbd->word_1 = SAR_TBD_EPDU | SAR_TBD_AAL0 |
				      ATM_CELL_PAYLOAD;
		अन्यथा
			tbd->word_1 = SAR_TBD_EPDU | SAR_TBD_AAL34 |
				      ATM_CELL_PAYLOAD;

		tbd->word_2 = IDT77252_PRV_PADDR(skb) + 4;
		tbd->word_3 = 0x00000000;
		tbd->word_4 = word4;
		अवरोध;

	हाल ATM_AAL5:
		tbd->word_1 = SAR_TBD_EPDU | SAR_TBD_AAL5 | skb->len;
		tbd->word_2 = IDT77252_PRV_PADDR(skb);
		tbd->word_3 = skb->len;
		tbd->word_4 = (vcc->vpi << SAR_TBD_VPI_SHIFT) |
			      (vcc->vci << SAR_TBD_VCI_SHIFT);
		अवरोध;

	हाल ATM_AAL1:
	हाल ATM_AAL2:
	शेष:
		prपूर्णांकk("%s: Traffic type not supported.\n", card->name);
		error = -EPROTONOSUPPORT;
		जाओ errout;
	पूर्ण

करोne:
	spin_lock_irqsave(&vc->scq->skblock, flags);
	skb_queue_tail(&vc->scq->pending, skb);

	जबतक ((skb = skb_dequeue(&vc->scq->pending))) अणु
		अगर (push_on_scq(card, vc, skb)) अणु
			skb_queue_head(&vc->scq->pending, skb);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vc->scq->skblock, flags);

	वापस 0;

errout:
	dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
			 skb->len, DMA_TO_DEVICE);
	वापस error;
पूर्ण

अटल अचिन्हित दीर्घ
get_मुक्त_scd(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < card->scd_size; i++) अणु
		अगर (!card->scd2vc[i]) अणु
			card->scd2vc[i] = vc;
			vc->scd_index = i;
			वापस card->scd_base + i * SAR_SRAM_SCD_SIZE;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
fill_scd(काष्ठा idt77252_dev *card, काष्ठा scq_info *scq, पूर्णांक class)
अणु
	ग_लिखो_sram(card, scq->scd, scq->paddr);
	ग_लिखो_sram(card, scq->scd + 1, 0x00000000);
	ग_लिखो_sram(card, scq->scd + 2, 0xffffffff);
	ग_लिखो_sram(card, scq->scd + 3, 0x00000000);
पूर्ण

अटल व्योम
clear_scd(काष्ठा idt77252_dev *card, काष्ठा scq_info *scq, पूर्णांक class)
अणु
	वापस;
पूर्ण

/*****************************************************************************/
/*                                                                           */
/* RSQ Handling                                                              */
/*                                                                           */
/*****************************************************************************/

अटल पूर्णांक
init_rsq(काष्ठा idt77252_dev *card)
अणु
	काष्ठा rsq_entry *rsqe;

	card->rsq.base = dma_alloc_coherent(&card->pcidev->dev, RSQSIZE,
					    &card->rsq.paddr, GFP_KERNEL);
	अगर (card->rsq.base == शून्य) अणु
		prपूर्णांकk("%s: can't allocate RSQ.\n", card->name);
		वापस -1;
	पूर्ण

	card->rsq.last = card->rsq.base + RSQ_NUM_ENTRIES - 1;
	card->rsq.next = card->rsq.last;
	क्रम (rsqe = card->rsq.base; rsqe <= card->rsq.last; rsqe++)
		rsqe->word_4 = 0;

	ग_लिखोl((अचिन्हित दीर्घ) card->rsq.last - (अचिन्हित दीर्घ) card->rsq.base,
	       SAR_REG_RSQH);
	ग_लिखोl(card->rsq.paddr, SAR_REG_RSQB);

	IPRINTK("%s: RSQ base at 0x%lx (0x%x).\n", card->name,
		(अचिन्हित दीर्घ) card->rsq.base,
		पढ़ोl(SAR_REG_RSQB));
	IPRINTK("%s: RSQ head = 0x%x, base = 0x%x, tail = 0x%x.\n",
		card->name,
		पढ़ोl(SAR_REG_RSQH),
		पढ़ोl(SAR_REG_RSQB),
		पढ़ोl(SAR_REG_RSQT));

	वापस 0;
पूर्ण

अटल व्योम
deinit_rsq(काष्ठा idt77252_dev *card)
अणु
	dma_मुक्त_coherent(&card->pcidev->dev, RSQSIZE,
			  card->rsq.base, card->rsq.paddr);
पूर्ण

अटल व्योम
dequeue_rx(काष्ठा idt77252_dev *card, काष्ठा rsq_entry *rsqe)
अणु
	काष्ठा aपंचांग_vcc *vcc;
	काष्ठा sk_buff *skb;
	काष्ठा rx_pool *rpp;
	काष्ठा vc_map *vc;
	u32 header, vpi, vci;
	u32 stat;
	पूर्णांक i;

	stat = le32_to_cpu(rsqe->word_4);

	अगर (stat & SAR_RSQE_IDLE) अणु
		RXPRINTK("%s: message about inactive connection.\n",
			 card->name);
		वापस;
	पूर्ण

	skb = sb_pool_skb(card, le32_to_cpu(rsqe->word_2));
	अगर (skb == शून्य) अणु
		prपूर्णांकk("%s: NULL skb in %s, rsqe: %08x %08x %08x %08x\n",
		       card->name, __func__,
		       le32_to_cpu(rsqe->word_1), le32_to_cpu(rsqe->word_2),
		       le32_to_cpu(rsqe->word_3), le32_to_cpu(rsqe->word_4));
		वापस;
	पूर्ण

	header = le32_to_cpu(rsqe->word_1);
	vpi = (header >> 16) & 0x00ff;
	vci = (header >>  0) & 0xffff;

	RXPRINTK("%s: SDU for %d.%d received in buffer 0x%p (data 0x%p).\n",
		 card->name, vpi, vci, skb, skb->data);

	अगर ((vpi >= (1 << card->vpibits)) || (vci != (vci & card->vcimask))) अणु
		prपूर्णांकk("%s: SDU received for out-of-range vc %u.%u\n",
		       card->name, vpi, vci);
		recycle_rx_skb(card, skb);
		वापस;
	पूर्ण

	vc = card->vcs[VPCI2VC(card, vpi, vci)];
	अगर (!vc || !test_bit(VCF_RX, &vc->flags)) अणु
		prपूर्णांकk("%s: SDU received on non RX vc %u.%u\n",
		       card->name, vpi, vci);
		recycle_rx_skb(card, skb);
		वापस;
	पूर्ण

	vcc = vc->rx_vcc;

	dma_sync_single_क्रम_cpu(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				skb_end_poपूर्णांकer(skb) - skb->data,
				DMA_FROM_DEVICE);

	अगर ((vcc->qos.aal == ATM_AAL0) ||
	    (vcc->qos.aal == ATM_AAL34)) अणु
		काष्ठा sk_buff *sb;
		अचिन्हित अक्षर *cell;
		u32 aal0;

		cell = skb->data;
		क्रम (i = (stat & SAR_RSQE_CELLCNT); i; i--) अणु
			अगर ((sb = dev_alloc_skb(64)) == शून्य) अणु
				prपूर्णांकk("%s: Can't allocate buffers for aal0.\n",
				       card->name);
				atomic_add(i, &vcc->stats->rx_drop);
				अवरोध;
			पूर्ण
			अगर (!aपंचांग_अक्षरge(vcc, sb->truesize)) अणु
				RXPRINTK("%s: atm_charge() dropped aal0 packets.\n",
					 card->name);
				atomic_add(i - 1, &vcc->stats->rx_drop);
				dev_kमुक्त_skb(sb);
				अवरोध;
			पूर्ण
			aal0 = (vpi << ATM_HDR_VPI_SHIFT) |
			       (vci << ATM_HDR_VCI_SHIFT);
			aal0 |= (stat & SAR_RSQE_EPDU) ? 0x00000002 : 0;
			aal0 |= (stat & SAR_RSQE_CLP)  ? 0x00000001 : 0;

			*((u32 *) sb->data) = aal0;
			skb_put(sb, माप(u32));
			skb_put_data(sb, cell, ATM_CELL_PAYLOAD);

			ATM_SKB(sb)->vcc = vcc;
			__net_बारtamp(sb);
			vcc->push(vcc, sb);
			atomic_inc(&vcc->stats->rx);

			cell += ATM_CELL_PAYLOAD;
		पूर्ण

		recycle_rx_skb(card, skb);
		वापस;
	पूर्ण
	अगर (vcc->qos.aal != ATM_AAL5) अणु
		prपूर्णांकk("%s: Unexpected AAL type in dequeue_rx(): %d.\n",
		       card->name, vcc->qos.aal);
		recycle_rx_skb(card, skb);
		वापस;
	पूर्ण
	skb->len = (stat & SAR_RSQE_CELLCNT) * ATM_CELL_PAYLOAD;

	rpp = &vc->rcv.rx_pool;

	__skb_queue_tail(&rpp->queue, skb);
	rpp->len += skb->len;

	अगर (stat & SAR_RSQE_EPDU) अणु
		अचिन्हित अक्षर *l1l2;
		अचिन्हित पूर्णांक len;

		l1l2 = (अचिन्हित अक्षर *) ((अचिन्हित दीर्घ) skb->data + skb->len - 6);

		len = (l1l2[0] << 8) | l1l2[1];
		len = len ? len : 0x10000;

		RXPRINTK("%s: PDU has %d bytes.\n", card->name, len);

		अगर ((len + 8 > rpp->len) || (len + (47 + 8) < rpp->len)) अणु
			RXPRINTK("%s: AAL5 PDU size mismatch: %d != %d. "
			         "(CDC: %08x)\n",
			         card->name, len, rpp->len, पढ़ोl(SAR_REG_CDC));
			recycle_rx_pool_skb(card, rpp);
			atomic_inc(&vcc->stats->rx_err);
			वापस;
		पूर्ण
		अगर (stat & SAR_RSQE_CRC) अणु
			RXPRINTK("%s: AAL5 CRC error.\n", card->name);
			recycle_rx_pool_skb(card, rpp);
			atomic_inc(&vcc->stats->rx_err);
			वापस;
		पूर्ण
		अगर (skb_queue_len(&rpp->queue) > 1) अणु
			काष्ठा sk_buff *sb;

			skb = dev_alloc_skb(rpp->len);
			अगर (!skb) अणु
				RXPRINTK("%s: Can't alloc RX skb.\n",
					 card->name);
				recycle_rx_pool_skb(card, rpp);
				atomic_inc(&vcc->stats->rx_err);
				वापस;
			पूर्ण
			अगर (!aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
				recycle_rx_pool_skb(card, rpp);
				dev_kमुक्त_skb(skb);
				वापस;
			पूर्ण
			skb_queue_walk(&rpp->queue, sb)
				skb_put_data(skb, sb->data, sb->len);

			recycle_rx_pool_skb(card, rpp);

			skb_trim(skb, len);
			ATM_SKB(skb)->vcc = vcc;
			__net_बारtamp(skb);

			vcc->push(vcc, skb);
			atomic_inc(&vcc->stats->rx);

			वापस;
		पूर्ण

		flush_rx_pool(card, rpp);

		अगर (!aपंचांग_अक्षरge(vcc, skb->truesize)) अणु
			recycle_rx_skb(card, skb);
			वापस;
		पूर्ण

		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb_end_poपूर्णांकer(skb) - skb->data,
				 DMA_FROM_DEVICE);
		sb_pool_हटाओ(card, skb);

		skb_trim(skb, len);
		ATM_SKB(skb)->vcc = vcc;
		__net_बारtamp(skb);

		vcc->push(vcc, skb);
		atomic_inc(&vcc->stats->rx);

		अगर (skb->truesize > SAR_FB_SIZE_3)
			add_rx_skb(card, 3, SAR_FB_SIZE_3, 1);
		अन्यथा अगर (skb->truesize > SAR_FB_SIZE_2)
			add_rx_skb(card, 2, SAR_FB_SIZE_2, 1);
		अन्यथा अगर (skb->truesize > SAR_FB_SIZE_1)
			add_rx_skb(card, 1, SAR_FB_SIZE_1, 1);
		अन्यथा
			add_rx_skb(card, 0, SAR_FB_SIZE_0, 1);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम
idt77252_rx(काष्ठा idt77252_dev *card)
अणु
	काष्ठा rsq_entry *rsqe;

	अगर (card->rsq.next == card->rsq.last)
		rsqe = card->rsq.base;
	अन्यथा
		rsqe = card->rsq.next + 1;

	अगर (!(le32_to_cpu(rsqe->word_4) & SAR_RSQE_VALID)) अणु
		RXPRINTK("%s: no entry in RSQ.\n", card->name);
		वापस;
	पूर्ण

	करो अणु
		dequeue_rx(card, rsqe);
		rsqe->word_4 = 0;
		card->rsq.next = rsqe;
		अगर (card->rsq.next == card->rsq.last)
			rsqe = card->rsq.base;
		अन्यथा
			rsqe = card->rsq.next + 1;
	पूर्ण जबतक (le32_to_cpu(rsqe->word_4) & SAR_RSQE_VALID);

	ग_लिखोl((अचिन्हित दीर्घ) card->rsq.next - (अचिन्हित दीर्घ) card->rsq.base,
	       SAR_REG_RSQH);
पूर्ण

अटल व्योम
idt77252_rx_raw(काष्ठा idt77252_dev *card)
अणु
	काष्ठा sk_buff	*queue;
	u32		head, tail;
	काष्ठा aपंचांग_vcc	*vcc;
	काष्ठा vc_map	*vc;
	काष्ठा sk_buff	*sb;

	अगर (card->raw_cell_head == शून्य) अणु
		u32 handle = le32_to_cpu(*(card->raw_cell_hnd + 1));
		card->raw_cell_head = sb_pool_skb(card, handle);
	पूर्ण

	queue = card->raw_cell_head;
	अगर (!queue)
		वापस;

	head = IDT77252_PRV_PADDR(queue) + (queue->data - queue->head - 16);
	tail = पढ़ोl(SAR_REG_RAWCT);

	dma_sync_single_क्रम_cpu(&card->pcidev->dev, IDT77252_PRV_PADDR(queue),
				skb_end_offset(queue) - 16,
				DMA_FROM_DEVICE);

	जबतक (head != tail) अणु
		अचिन्हित पूर्णांक vpi, vci;
		u32 header;

		header = le32_to_cpu(*(u32 *) &queue->data[0]);

		vpi = (header & ATM_HDR_VPI_MASK) >> ATM_HDR_VPI_SHIFT;
		vci = (header & ATM_HDR_VCI_MASK) >> ATM_HDR_VCI_SHIFT;

#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
		अगर (debug & DBG_RAW_CELL) अणु
			पूर्णांक i;

			prपूर्णांकk("%s: raw cell %x.%02x.%04x.%x.%x\n",
			       card->name, (header >> 28) & 0x000f,
			       (header >> 20) & 0x00ff,
			       (header >>  4) & 0xffff,
			       (header >>  1) & 0x0007,
			       (header >>  0) & 0x0001);
			क्रम (i = 16; i < 64; i++)
				prपूर्णांकk(" %02x", queue->data[i]);
			prपूर्णांकk("\n");
		पूर्ण
#पूर्ण_अगर

		अगर (vpi >= (1<<card->vpibits) || vci >= (1<<card->vcibits)) अणु
			RPRINTK("%s: SDU received for out-of-range vc %u.%u\n",
				card->name, vpi, vci);
			जाओ drop;
		पूर्ण

		vc = card->vcs[VPCI2VC(card, vpi, vci)];
		अगर (!vc || !test_bit(VCF_RX, &vc->flags)) अणु
			RPRINTK("%s: SDU received on non RX vc %u.%u\n",
				card->name, vpi, vci);
			जाओ drop;
		पूर्ण

		vcc = vc->rx_vcc;

		अगर (vcc->qos.aal != ATM_AAL0) अणु
			RPRINTK("%s: raw cell for non AAL0 vc %u.%u\n",
				card->name, vpi, vci);
			atomic_inc(&vcc->stats->rx_drop);
			जाओ drop;
		पूर्ण
	
		अगर ((sb = dev_alloc_skb(64)) == शून्य) अणु
			prपूर्णांकk("%s: Can't allocate buffers for AAL0.\n",
			       card->name);
			atomic_inc(&vcc->stats->rx_err);
			जाओ drop;
		पूर्ण

		अगर (!aपंचांग_अक्षरge(vcc, sb->truesize)) अणु
			RXPRINTK("%s: atm_charge() dropped AAL0 packets.\n",
				 card->name);
			dev_kमुक्त_skb(sb);
			जाओ drop;
		पूर्ण

		*((u32 *) sb->data) = header;
		skb_put(sb, माप(u32));
		skb_put_data(sb, &(queue->data[16]), ATM_CELL_PAYLOAD);

		ATM_SKB(sb)->vcc = vcc;
		__net_बारtamp(sb);
		vcc->push(vcc, sb);
		atomic_inc(&vcc->stats->rx);

drop:
		skb_pull(queue, 64);

		head = IDT77252_PRV_PADDR(queue)
					+ (queue->data - queue->head - 16);

		अगर (queue->len < 128) अणु
			काष्ठा sk_buff *next;
			u32 handle;

			head = le32_to_cpu(*(u32 *) &queue->data[0]);
			handle = le32_to_cpu(*(u32 *) &queue->data[4]);

			next = sb_pool_skb(card, handle);
			recycle_rx_skb(card, queue);

			अगर (next) अणु
				card->raw_cell_head = next;
				queue = card->raw_cell_head;
				dma_sync_single_क्रम_cpu(&card->pcidev->dev,
							IDT77252_PRV_PADDR(queue),
							(skb_end_poपूर्णांकer(queue) -
							 queue->data),
							DMA_FROM_DEVICE);
			पूर्ण अन्यथा अणु
				card->raw_cell_head = शून्य;
				prपूर्णांकk("%s: raw cell queue overrun\n",
				       card->name);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


/*****************************************************************************/
/*                                                                           */
/* TSQ Handling                                                              */
/*                                                                           */
/*****************************************************************************/

अटल पूर्णांक
init_tsq(काष्ठा idt77252_dev *card)
अणु
	काष्ठा tsq_entry *tsqe;

	card->tsq.base = dma_alloc_coherent(&card->pcidev->dev, RSQSIZE,
					    &card->tsq.paddr, GFP_KERNEL);
	अगर (card->tsq.base == शून्य) अणु
		prपूर्णांकk("%s: can't allocate TSQ.\n", card->name);
		वापस -1;
	पूर्ण

	card->tsq.last = card->tsq.base + TSQ_NUM_ENTRIES - 1;
	card->tsq.next = card->tsq.last;
	क्रम (tsqe = card->tsq.base; tsqe <= card->tsq.last; tsqe++)
		tsqe->word_2 = cpu_to_le32(SAR_TSQE_INVALID);

	ग_लिखोl(card->tsq.paddr, SAR_REG_TSQB);
	ग_लिखोl((अचिन्हित दीर्घ) card->tsq.next - (अचिन्हित दीर्घ) card->tsq.base,
	       SAR_REG_TSQH);

	वापस 0;
पूर्ण

अटल व्योम
deinit_tsq(काष्ठा idt77252_dev *card)
अणु
	dma_मुक्त_coherent(&card->pcidev->dev, TSQSIZE,
			  card->tsq.base, card->tsq.paddr);
पूर्ण

अटल व्योम
idt77252_tx(काष्ठा idt77252_dev *card)
अणु
	काष्ठा tsq_entry *tsqe;
	अचिन्हित पूर्णांक vpi, vci;
	काष्ठा vc_map *vc;
	u32 conn, stat;

	अगर (card->tsq.next == card->tsq.last)
		tsqe = card->tsq.base;
	अन्यथा
		tsqe = card->tsq.next + 1;

	TXPRINTK("idt77252_tx: tsq  %p: base %p, next %p, last %p\n", tsqe,
		 card->tsq.base, card->tsq.next, card->tsq.last);
	TXPRINTK("idt77252_tx: tsqb %08x, tsqt %08x, tsqh %08x, \n",
		 पढ़ोl(SAR_REG_TSQB),
		 पढ़ोl(SAR_REG_TSQT),
		 पढ़ोl(SAR_REG_TSQH));

	stat = le32_to_cpu(tsqe->word_2);

	अगर (stat & SAR_TSQE_INVALID)
		वापस;

	करो अणु
		TXPRINTK("tsqe: 0x%p [0x%08x 0x%08x]\n", tsqe,
			 le32_to_cpu(tsqe->word_1),
			 le32_to_cpu(tsqe->word_2));

		चयन (stat & SAR_TSQE_TYPE) अणु
		हाल SAR_TSQE_TYPE_TIMER:
			TXPRINTK("%s: Timer RollOver detected.\n", card->name);
			अवरोध;

		हाल SAR_TSQE_TYPE_IDLE:

			conn = le32_to_cpu(tsqe->word_1);

			अगर (SAR_TSQE_TAG(stat) == 0x10) अणु
#अगर_घोषित	NOTDEF
				prपूर्णांकk("%s: Connection %d halted.\n",
				       card->name,
				       le32_to_cpu(tsqe->word_1) & 0x1fff);
#पूर्ण_अगर
				अवरोध;
			पूर्ण

			vc = card->vcs[conn & 0x1fff];
			अगर (!vc) अणु
				prपूर्णांकk("%s: could not find VC from conn %d\n",
				       card->name, conn & 0x1fff);
				अवरोध;
			पूर्ण

			prपूर्णांकk("%s: Connection %d IDLE.\n",
			       card->name, vc->index);

			set_bit(VCF_IDLE, &vc->flags);
			अवरोध;

		हाल SAR_TSQE_TYPE_TSR:

			conn = le32_to_cpu(tsqe->word_1);

			vc = card->vcs[conn & 0x1fff];
			अगर (!vc) अणु
				prपूर्णांकk("%s: no VC at index %d\n",
				       card->name,
				       le32_to_cpu(tsqe->word_1) & 0x1fff);
				अवरोध;
			पूर्ण

			drain_scq(card, vc);
			अवरोध;

		हाल SAR_TSQE_TYPE_TBD_COMP:

			conn = le32_to_cpu(tsqe->word_1);

			vpi = (conn >> SAR_TBD_VPI_SHIFT) & 0x00ff;
			vci = (conn >> SAR_TBD_VCI_SHIFT) & 0xffff;

			अगर (vpi >= (1 << card->vpibits) ||
			    vci >= (1 << card->vcibits)) अणु
				prपूर्णांकk("%s: TBD complete: "
				       "out of range VPI.VCI %u.%u\n",
				       card->name, vpi, vci);
				अवरोध;
			पूर्ण

			vc = card->vcs[VPCI2VC(card, vpi, vci)];
			अगर (!vc) अणु
				prपूर्णांकk("%s: TBD complete: "
				       "no VC at VPI.VCI %u.%u\n",
				       card->name, vpi, vci);
				अवरोध;
			पूर्ण

			drain_scq(card, vc);
			अवरोध;
		पूर्ण

		tsqe->word_2 = cpu_to_le32(SAR_TSQE_INVALID);

		card->tsq.next = tsqe;
		अगर (card->tsq.next == card->tsq.last)
			tsqe = card->tsq.base;
		अन्यथा
			tsqe = card->tsq.next + 1;

		TXPRINTK("tsqe: %p: base %p, next %p, last %p\n", tsqe,
			 card->tsq.base, card->tsq.next, card->tsq.last);

		stat = le32_to_cpu(tsqe->word_2);

	पूर्ण जबतक (!(stat & SAR_TSQE_INVALID));

	ग_लिखोl((अचिन्हित दीर्घ)card->tsq.next - (अचिन्हित दीर्घ)card->tsq.base,
	       SAR_REG_TSQH);

	XPRINTK("idt77252_tx-after writel%d: TSQ head = 0x%x, tail = 0x%x, next = 0x%p.\n",
		card->index, पढ़ोl(SAR_REG_TSQH),
		पढ़ोl(SAR_REG_TSQT), card->tsq.next);
पूर्ण


अटल व्योम
tst_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा idt77252_dev *card = from_समयr(card, t, tst_समयr);
	अचिन्हित दीर्घ base, idle, jump;
	अचिन्हित दीर्घ flags;
	u32 pc;
	पूर्णांक e;

	spin_lock_irqsave(&card->tst_lock, flags);

	base = card->tst[card->tst_index];
	idle = card->tst[card->tst_index ^ 1];

	अगर (test_bit(TST_SWITCH_WAIT, &card->tst_state)) अणु
		jump = base + card->tst_size - 2;

		pc = पढ़ोl(SAR_REG_NOW) >> 2;
		अगर ((pc ^ idle) & ~(card->tst_size - 1)) अणु
			mod_समयr(&card->tst_समयr, jअगरfies + 1);
			जाओ out;
		पूर्ण

		clear_bit(TST_SWITCH_WAIT, &card->tst_state);

		card->tst_index ^= 1;
		ग_लिखो_sram(card, jump, TSTE_OPC_JMP | (base << 2));

		base = card->tst[card->tst_index];
		idle = card->tst[card->tst_index ^ 1];

		क्रम (e = 0; e < card->tst_size - 2; e++) अणु
			अगर (card->soft_tst[e].tste & TSTE_PUSH_IDLE) अणु
				ग_लिखो_sram(card, idle + e,
					   card->soft_tst[e].tste & TSTE_MASK);
				card->soft_tst[e].tste &= ~(TSTE_PUSH_IDLE);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(TST_SWITCH_PENDING, &card->tst_state)) अणु

		क्रम (e = 0; e < card->tst_size - 2; e++) अणु
			अगर (card->soft_tst[e].tste & TSTE_PUSH_ACTIVE) अणु
				ग_लिखो_sram(card, idle + e,
					   card->soft_tst[e].tste & TSTE_MASK);
				card->soft_tst[e].tste &= ~(TSTE_PUSH_ACTIVE);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			पूर्ण
		पूर्ण

		jump = base + card->tst_size - 2;

		ग_लिखो_sram(card, jump, TSTE_OPC_शून्य);
		set_bit(TST_SWITCH_WAIT, &card->tst_state);

		mod_समयr(&card->tst_समयr, jअगरfies + 1);
	पूर्ण

out:
	spin_unlock_irqrestore(&card->tst_lock, flags);
पूर्ण

अटल पूर्णांक
__fill_tst(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
	   पूर्णांक n, अचिन्हित पूर्णांक opc)
अणु
	अचिन्हित दीर्घ cl, avail;
	अचिन्हित दीर्घ idle;
	पूर्णांक e, r;
	u32 data;

	avail = card->tst_size - 2;
	क्रम (e = 0; e < avail; e++) अणु
		अगर (card->soft_tst[e].vc == शून्य)
			अवरोध;
	पूर्ण
	अगर (e >= avail) अणु
		prपूर्णांकk("%s: No free TST entries found\n", card->name);
		वापस -1;
	पूर्ण

	NPRINTK("%s: conn %d: first TST entry at %d.\n",
		card->name, vc ? vc->index : -1, e);

	r = n;
	cl = avail;
	data = opc & TSTE_OPC_MASK;
	अगर (vc && (opc != TSTE_OPC_शून्य))
		data = opc | vc->index;

	idle = card->tst[card->tst_index ^ 1];

	/*
	 * Fill Soft TST.
	 */
	जबतक (r > 0) अणु
		अगर ((cl >= avail) && (card->soft_tst[e].vc == शून्य)) अणु
			अगर (vc)
				card->soft_tst[e].vc = vc;
			अन्यथा
				card->soft_tst[e].vc = (व्योम *)-1;

			card->soft_tst[e].tste = data;
			अगर (समयr_pending(&card->tst_समयr))
				card->soft_tst[e].tste |= TSTE_PUSH_ACTIVE;
			अन्यथा अणु
				ग_लिखो_sram(card, idle + e, data);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			पूर्ण

			cl -= card->tst_size;
			r--;
		पूर्ण

		अगर (++e == avail)
			e = 0;
		cl += n;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
fill_tst(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc, पूर्णांक n, अचिन्हित पूर्णांक opc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&card->tst_lock, flags);

	res = __fill_tst(card, vc, n, opc);

	set_bit(TST_SWITCH_PENDING, &card->tst_state);
	अगर (!समयr_pending(&card->tst_समयr))
		mod_समयr(&card->tst_समयr, jअगरfies + 1);

	spin_unlock_irqrestore(&card->tst_lock, flags);
	वापस res;
पूर्ण

अटल पूर्णांक
__clear_tst(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc)
अणु
	अचिन्हित दीर्घ idle;
	पूर्णांक e;

	idle = card->tst[card->tst_index ^ 1];

	क्रम (e = 0; e < card->tst_size - 2; e++) अणु
		अगर (card->soft_tst[e].vc == vc) अणु
			card->soft_tst[e].vc = शून्य;

			card->soft_tst[e].tste = TSTE_OPC_VAR;
			अगर (समयr_pending(&card->tst_समयr))
				card->soft_tst[e].tste |= TSTE_PUSH_ACTIVE;
			अन्यथा अणु
				ग_लिखो_sram(card, idle + e, TSTE_OPC_VAR);
				card->soft_tst[e].tste |= TSTE_PUSH_IDLE;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
clear_tst(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&card->tst_lock, flags);

	res = __clear_tst(card, vc);

	set_bit(TST_SWITCH_PENDING, &card->tst_state);
	अगर (!समयr_pending(&card->tst_समयr))
		mod_समयr(&card->tst_समयr, jअगरfies + 1);

	spin_unlock_irqrestore(&card->tst_lock, flags);
	वापस res;
पूर्ण

अटल पूर्णांक
change_tst(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
	   पूर्णांक n, अचिन्हित पूर्णांक opc)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	spin_lock_irqsave(&card->tst_lock, flags);

	__clear_tst(card, vc);
	res = __fill_tst(card, vc, n, opc);

	set_bit(TST_SWITCH_PENDING, &card->tst_state);
	अगर (!समयr_pending(&card->tst_समयr))
		mod_समयr(&card->tst_समयr, jअगरfies + 1);

	spin_unlock_irqrestore(&card->tst_lock, flags);
	वापस res;
पूर्ण


अटल पूर्णांक
set_tct(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc)
अणु
	अचिन्हित दीर्घ tct;

	tct = (अचिन्हित दीर्घ) (card->tct_base + vc->index * SAR_SRAM_TCT_SIZE);

	चयन (vc->class) अणु
	हाल SCHED_CBR:
		OPRINTK("%s: writing TCT at 0x%lx, SCD 0x%lx.\n",
		        card->name, tct, vc->scq->scd);

		ग_लिखो_sram(card, tct + 0, TCT_CBR | vc->scq->scd);
		ग_लिखो_sram(card, tct + 1, 0);
		ग_लिखो_sram(card, tct + 2, 0);
		ग_लिखो_sram(card, tct + 3, 0);
		ग_लिखो_sram(card, tct + 4, 0);
		ग_लिखो_sram(card, tct + 5, 0);
		ग_लिखो_sram(card, tct + 6, 0);
		ग_लिखो_sram(card, tct + 7, 0);
		अवरोध;

	हाल SCHED_UBR:
		OPRINTK("%s: writing TCT at 0x%lx, SCD 0x%lx.\n",
		        card->name, tct, vc->scq->scd);

		ग_लिखो_sram(card, tct + 0, TCT_UBR | vc->scq->scd);
		ग_लिखो_sram(card, tct + 1, 0);
		ग_लिखो_sram(card, tct + 2, TCT_TSIF);
		ग_लिखो_sram(card, tct + 3, TCT_HALT | TCT_IDLE);
		ग_लिखो_sram(card, tct + 4, 0);
		ग_लिखो_sram(card, tct + 5, vc->init_er);
		ग_लिखो_sram(card, tct + 6, 0);
		ग_लिखो_sram(card, tct + 7, TCT_FLAG_UBR);
		अवरोध;

	हाल SCHED_VBR:
	हाल SCHED_ABR:
	शेष:
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

/*****************************************************************************/
/*                                                                           */
/* FBQ Handling                                                              */
/*                                                                           */
/*****************************************************************************/

अटल __अंतरभूत__ पूर्णांक
idt77252_fbq_full(काष्ठा idt77252_dev *card, पूर्णांक queue)
अणु
	वापस (पढ़ोl(SAR_REG_STAT) >> (16 + (queue << 2))) == 0x0f;
पूर्ण

अटल पूर्णांक
push_rx_skb(काष्ठा idt77252_dev *card, काष्ठा sk_buff *skb, पूर्णांक queue)
अणु
	अचिन्हित दीर्घ flags;
	u32 handle;
	u32 addr;

	skb->data = skb->head;
	skb_reset_tail_poपूर्णांकer(skb);
	skb->len = 0;

	skb_reserve(skb, 16);

	चयन (queue) अणु
	हाल 0:
		skb_put(skb, SAR_FB_SIZE_0);
		अवरोध;
	हाल 1:
		skb_put(skb, SAR_FB_SIZE_1);
		अवरोध;
	हाल 2:
		skb_put(skb, SAR_FB_SIZE_2);
		अवरोध;
	हाल 3:
		skb_put(skb, SAR_FB_SIZE_3);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (idt77252_fbq_full(card, queue))
		वापस -1;

	स_रखो(&skb->data[(skb->len & ~(0x3f)) - 64], 0, 2 * माप(u32));

	handle = IDT77252_PRV_POOL(skb);
	addr = IDT77252_PRV_PADDR(skb);

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl(handle, card->fbq[queue]);
	ग_लिखोl(addr, card->fbq[queue]);
	spin_unlock_irqrestore(&card->cmd_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम
add_rx_skb(काष्ठा idt77252_dev *card, पूर्णांक queue,
	   अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक count)
अणु
	काष्ठा sk_buff *skb;
	dma_addr_t paddr;
	u32 handle;

	जबतक (count--) अणु
		skb = dev_alloc_skb(size);
		अगर (!skb)
			वापस;

		अगर (sb_pool_add(card, skb, queue)) अणु
			prपूर्णांकk("%s: SB POOL full\n", __func__);
			जाओ outमुक्त;
		पूर्ण

		paddr = dma_map_single(&card->pcidev->dev, skb->data,
				       skb_end_poपूर्णांकer(skb) - skb->data,
				       DMA_FROM_DEVICE);
		IDT77252_PRV_PADDR(skb) = paddr;

		अगर (push_rx_skb(card, skb, queue)) अणु
			prपूर्णांकk("%s: FB QUEUE full\n", __func__);
			जाओ outunmap;
		पूर्ण
	पूर्ण

	वापस;

outunmap:
	dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
			 skb_end_poपूर्णांकer(skb) - skb->data, DMA_FROM_DEVICE);

	handle = IDT77252_PRV_POOL(skb);
	card->sbpool[POOL_QUEUE(handle)].skb[POOL_INDEX(handle)] = शून्य;

outमुक्त:
	dev_kमुक्त_skb(skb);
पूर्ण


अटल व्योम
recycle_rx_skb(काष्ठा idt77252_dev *card, काष्ठा sk_buff *skb)
अणु
	u32 handle = IDT77252_PRV_POOL(skb);
	पूर्णांक err;

	dma_sync_single_क्रम_device(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				   skb_end_poपूर्णांकer(skb) - skb->data,
				   DMA_FROM_DEVICE);

	err = push_rx_skb(card, skb, POOL_QUEUE(handle));
	अगर (err) अणु
		dma_unmap_single(&card->pcidev->dev, IDT77252_PRV_PADDR(skb),
				 skb_end_poपूर्णांकer(skb) - skb->data,
				 DMA_FROM_DEVICE);
		sb_pool_हटाओ(card, skb);
		dev_kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम
flush_rx_pool(काष्ठा idt77252_dev *card, काष्ठा rx_pool *rpp)
अणु
	skb_queue_head_init(&rpp->queue);
	rpp->len = 0;
पूर्ण

अटल व्योम
recycle_rx_pool_skb(काष्ठा idt77252_dev *card, काष्ठा rx_pool *rpp)
अणु
	काष्ठा sk_buff *skb, *पंचांगp;

	skb_queue_walk_safe(&rpp->queue, skb, पंचांगp)
		recycle_rx_skb(card, skb);

	flush_rx_pool(card, rpp);
पूर्ण

/*****************************************************************************/
/*                                                                           */
/* ATM Interface                                                             */
/*                                                                           */
/*****************************************************************************/

अटल व्योम
idt77252_phy_put(काष्ठा aपंचांग_dev *dev, अचिन्हित अक्षर value, अचिन्हित दीर्घ addr)
अणु
	ग_लिखो_utility(dev->dev_data, 0x100 + (addr & 0x1ff), value);
पूर्ण

अटल अचिन्हित अक्षर
idt77252_phy_get(काष्ठा aपंचांग_dev *dev, अचिन्हित दीर्घ addr)
अणु
	वापस पढ़ो_utility(dev->dev_data, 0x100 + (addr & 0x1ff));
पूर्ण

अटल अंतरभूत पूर्णांक
idt77252_send_skb(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb, पूर्णांक oam)
अणु
	काष्ठा aपंचांग_dev *dev = vcc->dev;
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा vc_map *vc = vcc->dev_data;
	पूर्णांक err;

	अगर (vc == शून्य) अणु
		prपूर्णांकk("%s: NULL connection in send().\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	अगर (!test_bit(VCF_TX, &vc->flags)) अणु
		prपूर्णांकk("%s: Trying to transmit on a non-tx VC.\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	चयन (vcc->qos.aal) अणु
	हाल ATM_AAL0:
	हाल ATM_AAL1:
	हाल ATM_AAL5:
		अवरोध;
	शेष:
		prपूर्णांकk("%s: Unsupported AAL: %d\n", card->name, vcc->qos.aal);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	अगर (skb_shinfo(skb)->nr_frags != 0) अणु
		prपूर्णांकk("%s: No scatter-gather yet.\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण
	ATM_SKB(skb)->vcc = vcc;

	err = queue_skb(card, vc, skb, oam);
	अगर (err) अणु
		atomic_inc(&vcc->stats->tx_err);
		dev_kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक idt77252_send(काष्ठा aपंचांग_vcc *vcc, काष्ठा sk_buff *skb)
अणु
	वापस idt77252_send_skb(vcc, skb, 0);
पूर्ण

अटल पूर्णांक
idt77252_send_oam(काष्ठा aपंचांग_vcc *vcc, व्योम *cell, पूर्णांक flags)
अणु
	काष्ठा aपंचांग_dev *dev = vcc->dev;
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(64);
	अगर (!skb) अणु
		prपूर्णांकk("%s: Out of memory in send_oam().\n", card->name);
		atomic_inc(&vcc->stats->tx_err);
		वापस -ENOMEM;
	पूर्ण
	refcount_add(skb->truesize, &sk_aपंचांग(vcc)->sk_wmem_alloc);

	skb_put_data(skb, cell, 52);

	वापस idt77252_send_skb(vcc, skb, 1);
पूर्ण

अटल __अंतरभूत__ अचिन्हित पूर्णांक
idt77252_fls(अचिन्हित पूर्णांक x)
अणु
	पूर्णांक r = 1;

	अगर (x == 0)
		वापस 0;
	अगर (x & 0xffff0000) अणु
		x >>= 16;
		r += 16;
	पूर्ण
	अगर (x & 0xff00) अणु
		x >>= 8;
		r += 8;
	पूर्ण
	अगर (x & 0xf0) अणु
		x >>= 4;
		r += 4;
	पूर्ण
	अगर (x & 0xc) अणु
		x >>= 2;
		r += 2;
	पूर्ण
	अगर (x & 0x2)
		r += 1;
	वापस r;
पूर्ण

अटल u16
idt77252_पूर्णांक_to_aपंचांगfp(अचिन्हित पूर्णांक rate)
अणु
	u16 m, e;

	अगर (rate == 0)
		वापस 0;
	e = idt77252_fls(rate) - 1;
	अगर (e < 9)
		m = (rate - (1 << e)) << (9 - e);
	अन्यथा अगर (e == 9)
		m = (rate - (1 << e));
	अन्यथा /* e > 9 */
		m = (rate - (1 << e)) >> (e - 9);
	वापस 0x4000 | (e << 9) | m;
पूर्ण

अटल u8
idt77252_rate_logindex(काष्ठा idt77252_dev *card, पूर्णांक pcr)
अणु
	u16 afp;

	afp = idt77252_पूर्णांक_to_aपंचांगfp(pcr < 0 ? -pcr : pcr);
	अगर (pcr < 0)
		वापस rate_to_log[(afp >> 5) & 0x1ff];
	वापस rate_to_log[((afp >> 5) + 1) & 0x1ff];
पूर्ण

अटल व्योम
idt77252_est_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा rate_estimator *est = from_समयr(est, t, समयr);
	काष्ठा vc_map *vc = est->vc;
	काष्ठा idt77252_dev *card = vc->card;
	अचिन्हित दीर्घ flags;
	u32 rate, cps;
	u64 ncells;
	u8 lacr;

	spin_lock_irqsave(&vc->lock, flags);
	अगर (!vc->estimator)
		जाओ out;
	ncells = est->cells;

	rate = ((u32)(ncells - est->last_cells)) << (7 - est->पूर्णांकerval);
	est->last_cells = ncells;
	est->avcps += ((दीर्घ)rate - (दीर्घ)est->avcps) >> est->ewma_log;
	est->cps = (est->avcps + 0x1f) >> 5;

	cps = est->cps;
	अगर (cps < (est->maxcps >> 4))
		cps = est->maxcps >> 4;

	lacr = idt77252_rate_logindex(card, cps);
	अगर (lacr > vc->max_er)
		lacr = vc->max_er;

	अगर (lacr != vc->lacr) अणु
		vc->lacr = lacr;
		ग_लिखोl(TCMDQ_LACR|(vc->lacr << 16)|vc->index, SAR_REG_TCMDQ);
	पूर्ण

	est->समयr.expires = jअगरfies + ((HZ / 4) << est->पूर्णांकerval);
	add_समयr(&est->समयr);

out:
	spin_unlock_irqrestore(&vc->lock, flags);
पूर्ण

अटल काष्ठा rate_estimator *
idt77252_init_est(काष्ठा vc_map *vc, पूर्णांक pcr)
अणु
	काष्ठा rate_estimator *est;

	est = kzalloc(माप(काष्ठा rate_estimator), GFP_KERNEL);
	अगर (!est)
		वापस शून्य;
	est->maxcps = pcr < 0 ? -pcr : pcr;
	est->cps = est->maxcps;
	est->avcps = est->cps << 5;
	est->vc = vc;

	est->पूर्णांकerval = 2;		/* XXX: make this configurable */
	est->ewma_log = 2;		/* XXX: make this configurable */
	समयr_setup(&est->समयr, idt77252_est_समयr, 0);
	mod_समयr(&est->समयr, jअगरfies + ((HZ / 4) << est->पूर्णांकerval));

	वापस est;
पूर्ण

अटल पूर्णांक
idt77252_init_cbr(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
		  काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक tst_मुक्त, tst_used, tst_entries;
	अचिन्हित दीर्घ पंचांगpl, modl;
	पूर्णांक tcr, tcra;

	अगर ((qos->txtp.max_pcr == 0) &&
	    (qos->txtp.pcr == 0) && (qos->txtp.min_pcr == 0)) अणु
		prपूर्णांकk("%s: trying to open a CBR VC with cell rate = 0\n",
		       card->name);
		वापस -EINVAL;
	पूर्ण

	tst_used = 0;
	tst_मुक्त = card->tst_मुक्त;
	अगर (test_bit(VCF_TX, &vc->flags))
		tst_used = vc->ntste;
	tst_मुक्त += tst_used;

	tcr = aपंचांग_pcr_goal(&qos->txtp);
	tcra = tcr >= 0 ? tcr : -tcr;

	TXPRINTK("%s: CBR target cell rate = %d\n", card->name, tcra);

	पंचांगpl = (अचिन्हित दीर्घ) tcra * ((अचिन्हित दीर्घ) card->tst_size - 2);
	modl = पंचांगpl % (अचिन्हित दीर्घ)card->utopia_pcr;

	tst_entries = (पूर्णांक) (पंचांगpl / card->utopia_pcr);
	अगर (tcr > 0) अणु
		अगर (modl > 0)
			tst_entries++;
	पूर्ण अन्यथा अगर (tcr == 0) अणु
		tst_entries = tst_मुक्त - SAR_TST_RESERVED;
		अगर (tst_entries <= 0) अणु
			prपूर्णांकk("%s: no CBR bandwidth free.\n", card->name);
			वापस -ENOSR;
		पूर्ण
	पूर्ण

	अगर (tst_entries == 0) अणु
		prपूर्णांकk("%s: selected CBR bandwidth < granularity.\n",
		       card->name);
		वापस -EINVAL;
	पूर्ण

	अगर (tst_entries > (tst_मुक्त - SAR_TST_RESERVED)) अणु
		prपूर्णांकk("%s: not enough CBR bandwidth free.\n", card->name);
		वापस -ENOSR;
	पूर्ण

	vc->ntste = tst_entries;

	card->tst_मुक्त = tst_मुक्त - tst_entries;
	अगर (test_bit(VCF_TX, &vc->flags)) अणु
		अगर (tst_used == tst_entries)
			वापस 0;

		OPRINTK("%s: modify %d -> %d entries in TST.\n",
			card->name, tst_used, tst_entries);
		change_tst(card, vc, tst_entries, TSTE_OPC_CBR);
		वापस 0;
	पूर्ण

	OPRINTK("%s: setting %d entries in TST.\n", card->name, tst_entries);
	fill_tst(card, vc, tst_entries, TSTE_OPC_CBR);
	वापस 0;
पूर्ण

अटल पूर्णांक
idt77252_init_ubr(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
		  काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	काष्ठा rate_estimator *est = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक tcr;

	spin_lock_irqsave(&vc->lock, flags);
	अगर (vc->estimator) अणु
		est = vc->estimator;
		vc->estimator = शून्य;
	पूर्ण
	spin_unlock_irqrestore(&vc->lock, flags);
	अगर (est) अणु
		del_समयr_sync(&est->समयr);
		kमुक्त(est);
	पूर्ण

	tcr = aपंचांग_pcr_goal(&qos->txtp);
	अगर (tcr == 0)
		tcr = card->link_pcr;

	vc->estimator = idt77252_init_est(vc, tcr);

	vc->class = SCHED_UBR;
	vc->init_er = idt77252_rate_logindex(card, tcr);
	vc->lacr = vc->init_er;
	अगर (tcr < 0)
		vc->max_er = vc->init_er;
	अन्यथा
		vc->max_er = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक
idt77252_init_tx(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
		 काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	पूर्णांक error;

	अगर (test_bit(VCF_TX, &vc->flags))
		वापस -EBUSY;

	चयन (qos->txtp.traffic_class) अणु
		हाल ATM_CBR:
			vc->class = SCHED_CBR;
			अवरोध;

		हाल ATM_UBR:
			vc->class = SCHED_UBR;
			अवरोध;

		हाल ATM_VBR:
		हाल ATM_ABR:
		शेष:
			वापस -EPROTONOSUPPORT;
	पूर्ण

	vc->scq = alloc_scq(card, vc->class);
	अगर (!vc->scq) अणु
		prपूर्णांकk("%s: can't get SCQ.\n", card->name);
		वापस -ENOMEM;
	पूर्ण

	vc->scq->scd = get_मुक्त_scd(card, vc);
	अगर (vc->scq->scd == 0) अणु
		prपूर्णांकk("%s: no SCD available.\n", card->name);
		मुक्त_scq(card, vc->scq);
		वापस -ENOMEM;
	पूर्ण

	fill_scd(card, vc->scq, vc->class);

	अगर (set_tct(card, vc)) अणु
		prपूर्णांकk("%s: class %d not supported.\n",
		       card->name, qos->txtp.traffic_class);

		card->scd2vc[vc->scd_index] = शून्य;
		मुक्त_scq(card, vc->scq);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	चयन (vc->class) अणु
		हाल SCHED_CBR:
			error = idt77252_init_cbr(card, vc, vcc, qos);
			अगर (error) अणु
				card->scd2vc[vc->scd_index] = शून्य;
				मुक्त_scq(card, vc->scq);
				वापस error;
			पूर्ण

			clear_bit(VCF_IDLE, &vc->flags);
			ग_लिखोl(TCMDQ_START | vc->index, SAR_REG_TCMDQ);
			अवरोध;

		हाल SCHED_UBR:
			error = idt77252_init_ubr(card, vc, vcc, qos);
			अगर (error) अणु
				card->scd2vc[vc->scd_index] = शून्य;
				मुक्त_scq(card, vc->scq);
				वापस error;
			पूर्ण

			set_bit(VCF_IDLE, &vc->flags);
			अवरोध;
	पूर्ण

	vc->tx_vcc = vcc;
	set_bit(VCF_TX, &vc->flags);
	वापस 0;
पूर्ण

अटल पूर्णांक
idt77252_init_rx(काष्ठा idt77252_dev *card, काष्ठा vc_map *vc,
		 काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr;
	u32 rcte = 0;

	अगर (test_bit(VCF_RX, &vc->flags))
		वापस -EBUSY;

	vc->rx_vcc = vcc;
	set_bit(VCF_RX, &vc->flags);

	अगर ((vcc->vci == 3) || (vcc->vci == 4))
		वापस 0;

	flush_rx_pool(card, &vc->rcv.rx_pool);

	rcte |= SAR_RCTE_CONNECTOPEN;
	rcte |= SAR_RCTE_RAWCELLINTEN;

	चयन (qos->aal) अणु
		हाल ATM_AAL0:
			rcte |= SAR_RCTE_RCQ;
			अवरोध;
		हाल ATM_AAL1:
			rcte |= SAR_RCTE_OAM; /* Let SAR drop Video */
			अवरोध;
		हाल ATM_AAL34:
			rcte |= SAR_RCTE_AAL34;
			अवरोध;
		हाल ATM_AAL5:
			rcte |= SAR_RCTE_AAL5;
			अवरोध;
		शेष:
			rcte |= SAR_RCTE_RCQ;
			अवरोध;
	पूर्ण

	अगर (qos->aal != ATM_AAL5)
		rcte |= SAR_RCTE_FBP_1;
	अन्यथा अगर (qos->rxtp.max_sdu > SAR_FB_SIZE_2)
		rcte |= SAR_RCTE_FBP_3;
	अन्यथा अगर (qos->rxtp.max_sdu > SAR_FB_SIZE_1)
		rcte |= SAR_RCTE_FBP_2;
	अन्यथा अगर (qos->rxtp.max_sdu > SAR_FB_SIZE_0)
		rcte |= SAR_RCTE_FBP_1;
	अन्यथा
		rcte |= SAR_RCTE_FBP_01;

	addr = card->rct_base + (vc->index << 2);

	OPRINTK("%s: writing RCT at 0x%lx\n", card->name, addr);
	ग_लिखो_sram(card, addr, rcte);

	spin_lock_irqsave(&card->cmd_lock, flags);
	ग_लिखोl(SAR_CMD_OPEN_CONNECTION | (addr << 2), SAR_REG_CMD);
	रुकोक्रम_idle(card);
	spin_unlock_irqrestore(&card->cmd_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
idt77252_खोलो(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांग_dev *dev = vcc->dev;
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा vc_map *vc;
	अचिन्हित पूर्णांक index;
	अचिन्हित पूर्णांक inuse;
	पूर्णांक error;
	पूर्णांक vci = vcc->vci;
	लघु vpi = vcc->vpi;

	अगर (vpi == ATM_VPI_UNSPEC || vci == ATM_VCI_UNSPEC)
		वापस 0;

	अगर (vpi >= (1 << card->vpibits)) अणु
		prपूर्णांकk("%s: unsupported VPI: %d\n", card->name, vpi);
		वापस -EINVAL;
	पूर्ण

	अगर (vci >= (1 << card->vcibits)) अणु
		prपूर्णांकk("%s: unsupported VCI: %d\n", card->name, vci);
		वापस -EINVAL;
	पूर्ण

	set_bit(ATM_VF_ADDR, &vcc->flags);

	mutex_lock(&card->mutex);

	OPRINTK("%s: opening vpi.vci: %d.%d\n", card->name, vpi, vci);

	चयन (vcc->qos.aal) अणु
	हाल ATM_AAL0:
	हाल ATM_AAL1:
	हाल ATM_AAL5:
		अवरोध;
	शेष:
		prपूर्णांकk("%s: Unsupported AAL: %d\n", card->name, vcc->qos.aal);
		mutex_unlock(&card->mutex);
		वापस -EPROTONOSUPPORT;
	पूर्ण

	index = VPCI2VC(card, vpi, vci);
	अगर (!card->vcs[index]) अणु
		card->vcs[index] = kzalloc(माप(काष्ठा vc_map), GFP_KERNEL);
		अगर (!card->vcs[index]) अणु
			prपूर्णांकk("%s: can't alloc vc in open()\n", card->name);
			mutex_unlock(&card->mutex);
			वापस -ENOMEM;
		पूर्ण
		card->vcs[index]->card = card;
		card->vcs[index]->index = index;

		spin_lock_init(&card->vcs[index]->lock);
	पूर्ण
	vc = card->vcs[index];

	vcc->dev_data = vc;

	IPRINTK("%s: idt77252_open: vc = %d (%d.%d) %s/%s (max RX SDU: %u)\n",
	        card->name, vc->index, vcc->vpi, vcc->vci,
	        vcc->qos.rxtp.traffic_class != ATM_NONE ? "rx" : "--",
	        vcc->qos.txtp.traffic_class != ATM_NONE ? "tx" : "--",
	        vcc->qos.rxtp.max_sdu);

	inuse = 0;
	अगर (vcc->qos.txtp.traffic_class != ATM_NONE &&
	    test_bit(VCF_TX, &vc->flags))
		inuse = 1;
	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE &&
	    test_bit(VCF_RX, &vc->flags))
		inuse += 2;

	अगर (inuse) अणु
		prपूर्णांकk("%s: %s vci already in use.\n", card->name,
		       inuse == 1 ? "tx" : inuse == 2 ? "rx" : "tx and rx");
		mutex_unlock(&card->mutex);
		वापस -EADDRINUSE;
	पूर्ण

	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु
		error = idt77252_init_tx(card, vc, vcc, &vcc->qos);
		अगर (error) अणु
			mutex_unlock(&card->mutex);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु
		error = idt77252_init_rx(card, vc, vcc, &vcc->qos);
		अगर (error) अणु
			mutex_unlock(&card->mutex);
			वापस error;
		पूर्ण
	पूर्ण

	set_bit(ATM_VF_READY, &vcc->flags);

	mutex_unlock(&card->mutex);
	वापस 0;
पूर्ण

अटल व्योम
idt77252_बंद(काष्ठा aपंचांग_vcc *vcc)
अणु
	काष्ठा aपंचांग_dev *dev = vcc->dev;
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा vc_map *vc = vcc->dev_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ समयout;

	mutex_lock(&card->mutex);

	IPRINTK("%s: idt77252_close: vc = %d (%d.%d)\n",
		card->name, vc->index, vcc->vpi, vcc->vci);

	clear_bit(ATM_VF_READY, &vcc->flags);

	अगर (vcc->qos.rxtp.traffic_class != ATM_NONE) अणु

		spin_lock_irqsave(&vc->lock, flags);
		clear_bit(VCF_RX, &vc->flags);
		vc->rx_vcc = शून्य;
		spin_unlock_irqrestore(&vc->lock, flags);

		अगर ((vcc->vci == 3) || (vcc->vci == 4))
			जाओ करोne;

		addr = card->rct_base + vc->index * SAR_SRAM_RCT_SIZE;

		spin_lock_irqsave(&card->cmd_lock, flags);
		ग_लिखोl(SAR_CMD_CLOSE_CONNECTION | (addr << 2), SAR_REG_CMD);
		रुकोक्रम_idle(card);
		spin_unlock_irqrestore(&card->cmd_lock, flags);

		अगर (skb_queue_len(&vc->rcv.rx_pool.queue) != 0) अणु
			DPRINTK("%s: closing a VC with pending rx buffers.\n",
				card->name);

			recycle_rx_pool_skb(card, &vc->rcv.rx_pool);
		पूर्ण
	पूर्ण

करोne:
	अगर (vcc->qos.txtp.traffic_class != ATM_NONE) अणु

		spin_lock_irqsave(&vc->lock, flags);
		clear_bit(VCF_TX, &vc->flags);
		clear_bit(VCF_IDLE, &vc->flags);
		clear_bit(VCF_RSV, &vc->flags);
		vc->tx_vcc = शून्य;

		अगर (vc->estimator) अणु
			del_समयr(&vc->estimator->समयr);
			kमुक्त(vc->estimator);
			vc->estimator = शून्य;
		पूर्ण
		spin_unlock_irqrestore(&vc->lock, flags);

		समयout = 5 * 1000;
		जबतक (atomic_पढ़ो(&vc->scq->used) > 0) अणु
			समयout = msleep_पूर्णांकerruptible(समयout);
			अगर (!समयout) अणु
				pr_warn("%s: SCQ drain timeout: %u used\n",
					card->name, atomic_पढ़ो(&vc->scq->used));
				अवरोध;
			पूर्ण
		पूर्ण

		ग_लिखोl(TCMDQ_HALT | vc->index, SAR_REG_TCMDQ);
		clear_scd(card, vc->scq, vc->class);

		अगर (vc->class == SCHED_CBR) अणु
			clear_tst(card, vc);
			card->tst_मुक्त += vc->ntste;
			vc->ntste = 0;
		पूर्ण

		card->scd2vc[vc->scd_index] = शून्य;
		मुक्त_scq(card, vc->scq);
	पूर्ण

	mutex_unlock(&card->mutex);
पूर्ण

अटल पूर्णांक
idt77252_change_qos(काष्ठा aपंचांग_vcc *vcc, काष्ठा aपंचांग_qos *qos, पूर्णांक flags)
अणु
	काष्ठा aपंचांग_dev *dev = vcc->dev;
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा vc_map *vc = vcc->dev_data;
	पूर्णांक error = 0;

	mutex_lock(&card->mutex);

	अगर (qos->txtp.traffic_class != ATM_NONE) अणु
	    	अगर (!test_bit(VCF_TX, &vc->flags)) अणु
			error = idt77252_init_tx(card, vc, vcc, qos);
			अगर (error)
				जाओ out;
		पूर्ण अन्यथा अणु
			चयन (qos->txtp.traffic_class) अणु
			हाल ATM_CBR:
				error = idt77252_init_cbr(card, vc, vcc, qos);
				अगर (error)
					जाओ out;
				अवरोध;

			हाल ATM_UBR:
				error = idt77252_init_ubr(card, vc, vcc, qos);
				अगर (error)
					जाओ out;

				अगर (!test_bit(VCF_IDLE, &vc->flags)) अणु
					ग_लिखोl(TCMDQ_LACR | (vc->lacr << 16) |
					       vc->index, SAR_REG_TCMDQ);
				पूर्ण
				अवरोध;

			हाल ATM_VBR:
			हाल ATM_ABR:
				error = -EOPNOTSUPP;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर ((qos->rxtp.traffic_class != ATM_NONE) &&
	    !test_bit(VCF_RX, &vc->flags)) अणु
		error = idt77252_init_rx(card, vc, vcc, qos);
		अगर (error)
			जाओ out;
	पूर्ण

	स_नकल(&vcc->qos, qos, माप(काष्ठा aपंचांग_qos));

	set_bit(ATM_VF_HASQOS, &vcc->flags);

out:
	mutex_unlock(&card->mutex);
	वापस error;
पूर्ण

अटल पूर्णांक
idt77252_proc_पढ़ो(काष्ठा aपंचांग_dev *dev, loff_t * pos, अक्षर *page)
अणु
	काष्ठा idt77252_dev *card = dev->dev_data;
	पूर्णांक i, left;

	left = (पूर्णांक) *pos;
	अगर (!left--)
		वापस प्र_लिखो(page, "IDT77252 Interrupts:\n");
	अगर (!left--)
		वापस प्र_लिखो(page, "TSIF:  %lu\n", card->irqstat[15]);
	अगर (!left--)
		वापस प्र_लिखो(page, "TXICP: %lu\n", card->irqstat[14]);
	अगर (!left--)
		वापस प्र_लिखो(page, "TSQF:  %lu\n", card->irqstat[12]);
	अगर (!left--)
		वापस प्र_लिखो(page, "TMROF: %lu\n", card->irqstat[11]);
	अगर (!left--)
		वापस प्र_लिखो(page, "PHYI:  %lu\n", card->irqstat[10]);
	अगर (!left--)
		वापस प्र_लिखो(page, "FBQ3A: %lu\n", card->irqstat[8]);
	अगर (!left--)
		वापस प्र_लिखो(page, "FBQ2A: %lu\n", card->irqstat[7]);
	अगर (!left--)
		वापस प्र_लिखो(page, "RSQF:  %lu\n", card->irqstat[6]);
	अगर (!left--)
		वापस प्र_लिखो(page, "EPDU:  %lu\n", card->irqstat[5]);
	अगर (!left--)
		वापस प्र_लिखो(page, "RAWCF: %lu\n", card->irqstat[4]);
	अगर (!left--)
		वापस प्र_लिखो(page, "FBQ1A: %lu\n", card->irqstat[3]);
	अगर (!left--)
		वापस प्र_लिखो(page, "FBQ0A: %lu\n", card->irqstat[2]);
	अगर (!left--)
		वापस प्र_लिखो(page, "RSQAF: %lu\n", card->irqstat[1]);
	अगर (!left--)
		वापस प्र_लिखो(page, "IDT77252 Transmit Connection Table:\n");

	क्रम (i = 0; i < card->tct_size; i++) अणु
		अचिन्हित दीर्घ tct;
		काष्ठा aपंचांग_vcc *vcc;
		काष्ठा vc_map *vc;
		अक्षर *p;

		vc = card->vcs[i];
		अगर (!vc)
			जारी;

		vcc = शून्य;
		अगर (vc->tx_vcc)
			vcc = vc->tx_vcc;
		अगर (!vcc)
			जारी;
		अगर (left--)
			जारी;

		p = page;
		p += प्र_लिखो(p, "  %4u: %u.%u: ", i, vcc->vpi, vcc->vci);
		tct = (अचिन्हित दीर्घ) (card->tct_base + i * SAR_SRAM_TCT_SIZE);

		क्रम (i = 0; i < 8; i++)
			p += प्र_लिखो(p, " %08x", पढ़ो_sram(card, tct + i));
		p += प्र_लिखो(p, "\n");
		वापस p - page;
	पूर्ण
	वापस 0;
पूर्ण

/*****************************************************************************/
/*                                                                           */
/* Interrupt handler                                                         */
/*                                                                           */
/*****************************************************************************/

अटल व्योम
idt77252_collect_stat(काष्ठा idt77252_dev *card)
अणु
	(व्योम) पढ़ोl(SAR_REG_CDC);
	(व्योम) पढ़ोl(SAR_REG_VPEC);
	(व्योम) पढ़ोl(SAR_REG_ICC);

पूर्ण

अटल irqवापस_t
idt77252_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा idt77252_dev *card = dev_id;
	u32 stat;

	stat = पढ़ोl(SAR_REG_STAT) & 0xffff;
	अगर (!stat)	/* no पूर्णांकerrupt क्रम us */
		वापस IRQ_NONE;

	अगर (test_and_set_bit(IDT77252_BIT_INTERRUPT, &card->flags)) अणु
		prपूर्णांकk("%s: Re-entering irq_handler()\n", card->name);
		जाओ out;
	पूर्ण

	ग_लिखोl(stat, SAR_REG_STAT);	/* reset पूर्णांकerrupt */

	अगर (stat & SAR_STAT_TSIF) अणु	/* entry written to TSQ  */
		INTPRINTK("%s: TSIF\n", card->name);
		card->irqstat[15]++;
		idt77252_tx(card);
	पूर्ण
	अगर (stat & SAR_STAT_TXICP) अणु	/* Incomplete CS-PDU has  */
		INTPRINTK("%s: TXICP\n", card->name);
		card->irqstat[14]++;
#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
		idt77252_tx_dump(card);
#पूर्ण_अगर
	पूर्ण
	अगर (stat & SAR_STAT_TSQF) अणु	/* TSQ 7/8 full           */
		INTPRINTK("%s: TSQF\n", card->name);
		card->irqstat[12]++;
		idt77252_tx(card);
	पूर्ण
	अगर (stat & SAR_STAT_TMROF) अणु	/* Timer overflow         */
		INTPRINTK("%s: TMROF\n", card->name);
		card->irqstat[11]++;
		idt77252_collect_stat(card);
	पूर्ण

	अगर (stat & SAR_STAT_EPDU) अणु	/* Got complete CS-PDU    */
		INTPRINTK("%s: EPDU\n", card->name);
		card->irqstat[5]++;
		idt77252_rx(card);
	पूर्ण
	अगर (stat & SAR_STAT_RSQAF) अणु	/* RSQ is 7/8 full        */
		INTPRINTK("%s: RSQAF\n", card->name);
		card->irqstat[1]++;
		idt77252_rx(card);
	पूर्ण
	अगर (stat & SAR_STAT_RSQF) अणु	/* RSQ is full            */
		INTPRINTK("%s: RSQF\n", card->name);
		card->irqstat[6]++;
		idt77252_rx(card);
	पूर्ण
	अगर (stat & SAR_STAT_RAWCF) अणु	/* Raw cell received      */
		INTPRINTK("%s: RAWCF\n", card->name);
		card->irqstat[4]++;
		idt77252_rx_raw(card);
	पूर्ण

	अगर (stat & SAR_STAT_PHYI) अणु	/* PHY device पूर्णांकerrupt   */
		INTPRINTK("%s: PHYI", card->name);
		card->irqstat[10]++;
		अगर (card->aपंचांगdev->phy && card->aपंचांगdev->phy->पूर्णांकerrupt)
			card->aपंचांगdev->phy->पूर्णांकerrupt(card->aपंचांगdev);
	पूर्ण

	अगर (stat & (SAR_STAT_FBQ0A | SAR_STAT_FBQ1A |
		    SAR_STAT_FBQ2A | SAR_STAT_FBQ3A)) अणु

		ग_लिखोl(पढ़ोl(SAR_REG_CFG) & ~(SAR_CFG_FBIE), SAR_REG_CFG);

		INTPRINTK("%s: FBQA: %04x\n", card->name, stat);

		अगर (stat & SAR_STAT_FBQ0A)
			card->irqstat[2]++;
		अगर (stat & SAR_STAT_FBQ1A)
			card->irqstat[3]++;
		अगर (stat & SAR_STAT_FBQ2A)
			card->irqstat[7]++;
		अगर (stat & SAR_STAT_FBQ3A)
			card->irqstat[8]++;

		schedule_work(&card->tqueue);
	पूर्ण

out:
	clear_bit(IDT77252_BIT_INTERRUPT, &card->flags);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
idt77252_softपूर्णांक(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा idt77252_dev *card =
		container_of(work, काष्ठा idt77252_dev, tqueue);
	u32 stat;
	पूर्णांक करोne;

	क्रम (करोne = 1; ; करोne = 1) अणु
		stat = पढ़ोl(SAR_REG_STAT) >> 16;

		अगर ((stat & 0x0f) < SAR_FBQ0_HIGH) अणु
			add_rx_skb(card, 0, SAR_FB_SIZE_0, 32);
			करोne = 0;
		पूर्ण

		stat >>= 4;
		अगर ((stat & 0x0f) < SAR_FBQ1_HIGH) अणु
			add_rx_skb(card, 1, SAR_FB_SIZE_1, 32);
			करोne = 0;
		पूर्ण

		stat >>= 4;
		अगर ((stat & 0x0f) < SAR_FBQ2_HIGH) अणु
			add_rx_skb(card, 2, SAR_FB_SIZE_2, 32);
			करोne = 0;
		पूर्ण

		stat >>= 4;
		अगर ((stat & 0x0f) < SAR_FBQ3_HIGH) अणु
			add_rx_skb(card, 3, SAR_FB_SIZE_3, 32);
			करोne = 0;
		पूर्ण

		अगर (करोne)
			अवरोध;
	पूर्ण

	ग_लिखोl(पढ़ोl(SAR_REG_CFG) | SAR_CFG_FBIE, SAR_REG_CFG);
पूर्ण


अटल पूर्णांक
खोलो_card_oam(काष्ठा idt77252_dev *card)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr;
	काष्ठा vc_map *vc;
	पूर्णांक vpi, vci;
	पूर्णांक index;
	u32 rcte;

	क्रम (vpi = 0; vpi < (1 << card->vpibits); vpi++) अणु
		क्रम (vci = 3; vci < 5; vci++) अणु
			index = VPCI2VC(card, vpi, vci);

			vc = kzalloc(माप(काष्ठा vc_map), GFP_KERNEL);
			अगर (!vc) अणु
				prपूर्णांकk("%s: can't alloc vc\n", card->name);
				वापस -ENOMEM;
			पूर्ण
			vc->index = index;
			card->vcs[index] = vc;

			flush_rx_pool(card, &vc->rcv.rx_pool);

			rcte = SAR_RCTE_CONNECTOPEN |
			       SAR_RCTE_RAWCELLINTEN |
			       SAR_RCTE_RCQ |
			       SAR_RCTE_FBP_1;

			addr = card->rct_base + (vc->index << 2);
			ग_लिखो_sram(card, addr, rcte);

			spin_lock_irqsave(&card->cmd_lock, flags);
			ग_लिखोl(SAR_CMD_OPEN_CONNECTION | (addr << 2),
			       SAR_REG_CMD);
			रुकोक्रम_idle(card);
			spin_unlock_irqrestore(&card->cmd_lock, flags);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
बंद_card_oam(काष्ठा idt77252_dev *card)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ addr;
	काष्ठा vc_map *vc;
	पूर्णांक vpi, vci;
	पूर्णांक index;

	क्रम (vpi = 0; vpi < (1 << card->vpibits); vpi++) अणु
		क्रम (vci = 3; vci < 5; vci++) अणु
			index = VPCI2VC(card, vpi, vci);
			vc = card->vcs[index];

			addr = card->rct_base + vc->index * SAR_SRAM_RCT_SIZE;

			spin_lock_irqsave(&card->cmd_lock, flags);
			ग_लिखोl(SAR_CMD_CLOSE_CONNECTION | (addr << 2),
			       SAR_REG_CMD);
			रुकोक्रम_idle(card);
			spin_unlock_irqrestore(&card->cmd_lock, flags);

			अगर (skb_queue_len(&vc->rcv.rx_pool.queue) != 0) अणु
				DPRINTK("%s: closing a VC "
					"with pending rx buffers.\n",
					card->name);

				recycle_rx_pool_skb(card, &vc->rcv.rx_pool);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
खोलो_card_ubr0(काष्ठा idt77252_dev *card)
अणु
	काष्ठा vc_map *vc;

	vc = kzalloc(माप(काष्ठा vc_map), GFP_KERNEL);
	अगर (!vc) अणु
		prपूर्णांकk("%s: can't alloc vc\n", card->name);
		वापस -ENOMEM;
	पूर्ण
	card->vcs[0] = vc;
	vc->class = SCHED_UBR0;

	vc->scq = alloc_scq(card, vc->class);
	अगर (!vc->scq) अणु
		prपूर्णांकk("%s: can't get SCQ.\n", card->name);
		वापस -ENOMEM;
	पूर्ण

	card->scd2vc[0] = vc;
	vc->scd_index = 0;
	vc->scq->scd = card->scd_base;

	fill_scd(card, vc->scq, vc->class);

	ग_लिखो_sram(card, card->tct_base + 0, TCT_UBR | card->scd_base);
	ग_लिखो_sram(card, card->tct_base + 1, 0);
	ग_लिखो_sram(card, card->tct_base + 2, 0);
	ग_लिखो_sram(card, card->tct_base + 3, 0);
	ग_लिखो_sram(card, card->tct_base + 4, 0);
	ग_लिखो_sram(card, card->tct_base + 5, 0);
	ग_लिखो_sram(card, card->tct_base + 6, 0);
	ग_लिखो_sram(card, card->tct_base + 7, TCT_FLAG_UBR);

	clear_bit(VCF_IDLE, &vc->flags);
	ग_लिखोl(TCMDQ_START | 0, SAR_REG_TCMDQ);
	वापस 0;
पूर्ण

अटल पूर्णांक
idt77252_dev_खोलो(काष्ठा idt77252_dev *card)
अणु
	u32 conf;

	अगर (!test_bit(IDT77252_BIT_INIT, &card->flags)) अणु
		prपूर्णांकk("%s: SAR not yet initialized.\n", card->name);
		वापस -1;
	पूर्ण

	conf = SAR_CFG_RXPTH|	/* enable receive path                  */
	    SAR_RX_DELAY |	/* पूर्णांकerrupt on complete PDU		*/
	    SAR_CFG_RAWIE |	/* पूर्णांकerrupt enable on raw cells        */
	    SAR_CFG_RQFIE |	/* पूर्णांकerrupt on RSQ almost full         */
	    SAR_CFG_TMOIE |	/* पूर्णांकerrupt on समयr overflow          */
	    SAR_CFG_FBIE |	/* पूर्णांकerrupt on low मुक्त buffers        */
	    SAR_CFG_TXEN |	/* transmit operation enable            */
	    SAR_CFG_TXINT |	/* पूर्णांकerrupt on transmit status         */
	    SAR_CFG_TXUIE |	/* पूर्णांकerrupt on transmit underrun       */
	    SAR_CFG_TXSFI |	/* पूर्णांकerrupt on TSQ almost full         */
	    SAR_CFG_PHYIE	/* enable PHY पूर्णांकerrupts		*/
	    ;

#अगर_घोषित CONFIG_ATM_IDT77252_RCV_ALL
	/* Test RAW cell receive. */
	conf |= SAR_CFG_VPECA;
#पूर्ण_अगर

	ग_लिखोl(पढ़ोl(SAR_REG_CFG) | conf, SAR_REG_CFG);

	अगर (खोलो_card_oam(card)) अणु
		prपूर्णांकk("%s: Error initializing OAM.\n", card->name);
		वापस -1;
	पूर्ण

	अगर (खोलो_card_ubr0(card)) अणु
		prपूर्णांकk("%s: Error initializing UBR0.\n", card->name);
		वापस -1;
	पूर्ण

	IPRINTK("%s: opened IDT77252 ABR SAR.\n", card->name);
	वापस 0;
पूर्ण

अटल व्योम idt77252_dev_बंद(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा idt77252_dev *card = dev->dev_data;
	u32 conf;

	बंद_card_oam(card);

	conf = SAR_CFG_RXPTH |	/* enable receive path           */
	    SAR_RX_DELAY |	/* पूर्णांकerrupt on complete PDU     */
	    SAR_CFG_RAWIE |	/* पूर्णांकerrupt enable on raw cells */
	    SAR_CFG_RQFIE |	/* पूर्णांकerrupt on RSQ almost full  */
	    SAR_CFG_TMOIE |	/* पूर्णांकerrupt on समयr overflow   */
	    SAR_CFG_FBIE |	/* पूर्णांकerrupt on low मुक्त buffers */
	    SAR_CFG_TXEN |	/* transmit operation enable     */
	    SAR_CFG_TXINT |	/* पूर्णांकerrupt on transmit status  */
	    SAR_CFG_TXUIE |	/* पूर्णांकerrupt on xmit underrun    */
	    SAR_CFG_TXSFI	/* पूर्णांकerrupt on TSQ almost full  */
	    ;

	ग_लिखोl(पढ़ोl(SAR_REG_CFG) & ~(conf), SAR_REG_CFG);

	DIPRINTK("%s: closed IDT77252 ABR SAR.\n", card->name);
पूर्ण


/*****************************************************************************/
/*                                                                           */
/* Initialisation and Deinitialization of IDT77252                           */
/*                                                                           */
/*****************************************************************************/


अटल व्योम
deinit_card(काष्ठा idt77252_dev *card)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक i, j;

	अगर (!test_bit(IDT77252_BIT_INIT, &card->flags)) अणु
		prपूर्णांकk("%s: SAR not yet initialized.\n", card->name);
		वापस;
	पूर्ण
	DIPRINTK("idt77252: deinitialize card %u\n", card->index);

	ग_लिखोl(0, SAR_REG_CFG);

	अगर (card->aपंचांगdev)
		aपंचांग_dev_deरेजिस्टर(card->aपंचांगdev);

	क्रम (i = 0; i < 4; i++) अणु
		क्रम (j = 0; j < FBQ_SIZE; j++) अणु
			skb = card->sbpool[i].skb[j];
			अगर (skb) अणु
				dma_unmap_single(&card->pcidev->dev,
						 IDT77252_PRV_PADDR(skb),
						 (skb_end_poपूर्णांकer(skb) -
						  skb->data),
						 DMA_FROM_DEVICE);
				card->sbpool[i].skb[j] = शून्य;
				dev_kमुक्त_skb(skb);
			पूर्ण
		पूर्ण
	पूर्ण

	vमुक्त(card->soft_tst);

	vमुक्त(card->scd2vc);

	vमुक्त(card->vcs);

	अगर (card->raw_cell_hnd) अणु
		dma_मुक्त_coherent(&card->pcidev->dev, 2 * माप(u32),
				  card->raw_cell_hnd, card->raw_cell_paddr);
	पूर्ण

	अगर (card->rsq.base) अणु
		DIPRINTK("%s: Release RSQ ...\n", card->name);
		deinit_rsq(card);
	पूर्ण

	अगर (card->tsq.base) अणु
		DIPRINTK("%s: Release TSQ ...\n", card->name);
		deinit_tsq(card);
	पूर्ण

	DIPRINTK("idt77252: Release IRQ.\n");
	मुक्त_irq(card->pcidev->irq, card);

	क्रम (i = 0; i < 4; i++) अणु
		अगर (card->fbq[i])
			iounmap(card->fbq[i]);
	पूर्ण

	अगर (card->membase)
		iounmap(card->membase);

	clear_bit(IDT77252_BIT_INIT, &card->flags);
	DIPRINTK("%s: Card deinitialized.\n", card->name);
पूर्ण


अटल व्योम init_sram(काष्ठा idt77252_dev *card)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < card->sramsize; i += 4)
		ग_लिखो_sram(card, (i >> 2), 0);

	/* set SRAM layout क्रम THIS card */
	अगर (card->sramsize == (512 * 1024)) अणु
		card->tct_base = SAR_SRAM_TCT_128_BASE;
		card->tct_size = (SAR_SRAM_TCT_128_TOP - card->tct_base + 1)
		    / SAR_SRAM_TCT_SIZE;
		card->rct_base = SAR_SRAM_RCT_128_BASE;
		card->rct_size = (SAR_SRAM_RCT_128_TOP - card->rct_base + 1)
		    / SAR_SRAM_RCT_SIZE;
		card->rt_base = SAR_SRAM_RT_128_BASE;
		card->scd_base = SAR_SRAM_SCD_128_BASE;
		card->scd_size = (SAR_SRAM_SCD_128_TOP - card->scd_base + 1)
		    / SAR_SRAM_SCD_SIZE;
		card->tst[0] = SAR_SRAM_TST1_128_BASE;
		card->tst[1] = SAR_SRAM_TST2_128_BASE;
		card->tst_size = SAR_SRAM_TST1_128_TOP - card->tst[0] + 1;
		card->abrst_base = SAR_SRAM_ABRSTD_128_BASE;
		card->abrst_size = SAR_ABRSTD_SIZE_8K;
		card->fअगरo_base = SAR_SRAM_FIFO_128_BASE;
		card->fअगरo_size = SAR_RXFD_SIZE_32K;
	पूर्ण अन्यथा अणु
		card->tct_base = SAR_SRAM_TCT_32_BASE;
		card->tct_size = (SAR_SRAM_TCT_32_TOP - card->tct_base + 1)
		    / SAR_SRAM_TCT_SIZE;
		card->rct_base = SAR_SRAM_RCT_32_BASE;
		card->rct_size = (SAR_SRAM_RCT_32_TOP - card->rct_base + 1)
		    / SAR_SRAM_RCT_SIZE;
		card->rt_base = SAR_SRAM_RT_32_BASE;
		card->scd_base = SAR_SRAM_SCD_32_BASE;
		card->scd_size = (SAR_SRAM_SCD_32_TOP - card->scd_base + 1)
		    / SAR_SRAM_SCD_SIZE;
		card->tst[0] = SAR_SRAM_TST1_32_BASE;
		card->tst[1] = SAR_SRAM_TST2_32_BASE;
		card->tst_size = (SAR_SRAM_TST1_32_TOP - card->tst[0] + 1);
		card->abrst_base = SAR_SRAM_ABRSTD_32_BASE;
		card->abrst_size = SAR_ABRSTD_SIZE_1K;
		card->fअगरo_base = SAR_SRAM_FIFO_32_BASE;
		card->fअगरo_size = SAR_RXFD_SIZE_4K;
	पूर्ण

	/* Initialize TCT */
	क्रम (i = 0; i < card->tct_size; i++) अणु
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 0, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 1, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 2, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 3, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 4, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 5, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 6, 0);
		ग_लिखो_sram(card, i * SAR_SRAM_TCT_SIZE + 7, 0);
	पूर्ण

	/* Initialize RCT */
	क्रम (i = 0; i < card->rct_size; i++) अणु
		ग_लिखो_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE,
				    (u32) SAR_RCTE_RAWCELLINTEN);
		ग_लिखो_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 1,
				    (u32) 0);
		ग_लिखो_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 2,
				    (u32) 0);
		ग_लिखो_sram(card, card->rct_base + i * SAR_SRAM_RCT_SIZE + 3,
				    (u32) 0xffffffff);
	पूर्ण

	ग_लिखोl((SAR_FBQ0_LOW << 28) | (SAR_FB_SIZE_0 / 48), SAR_REG_FBQS0);
	ग_लिखोl((SAR_FBQ1_LOW << 28) | (SAR_FB_SIZE_1 / 48), SAR_REG_FBQS1);
	ग_लिखोl((SAR_FBQ2_LOW << 28) | (SAR_FB_SIZE_2 / 48), SAR_REG_FBQS2);
	ग_लिखोl((SAR_FBQ3_LOW << 28) | (SAR_FB_SIZE_3 / 48), SAR_REG_FBQS3);

	/* Initialize rate table  */
	क्रम (i = 0; i < 256; i++) अणु
		ग_लिखो_sram(card, card->rt_base + i, log_to_rate[i]);
	पूर्ण

	क्रम (i = 0; i < 128; i++) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp  = rate_to_log[(i << 2) + 0] << 0;
		पंचांगp |= rate_to_log[(i << 2) + 1] << 8;
		पंचांगp |= rate_to_log[(i << 2) + 2] << 16;
		पंचांगp |= rate_to_log[(i << 2) + 3] << 24;
		ग_लिखो_sram(card, card->rt_base + 256 + i, पंचांगp);
	पूर्ण

#अगर 0 /* Fill RDF and AIR tables. */
	क्रम (i = 0; i < 128; i++) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = RDF[0][(i << 1) + 0] << 16;
		पंचांगp |= RDF[0][(i << 1) + 1] << 0;
		ग_लिखो_sram(card, card->rt_base + 512 + i, पंचांगp);
	पूर्ण

	क्रम (i = 0; i < 128; i++) अणु
		अचिन्हित पूर्णांक पंचांगp;

		पंचांगp = AIR[0][(i << 1) + 0] << 16;
		पंचांगp |= AIR[0][(i << 1) + 1] << 0;
		ग_लिखो_sram(card, card->rt_base + 640 + i, पंचांगp);
	पूर्ण
#पूर्ण_अगर

	IPRINTK("%s: initialize rate table ...\n", card->name);
	ग_लिखोl(card->rt_base << 2, SAR_REG_RTBL);

	/* Initialize TSTs */
	IPRINTK("%s: initialize TST ...\n", card->name);
	card->tst_मुक्त = card->tst_size - 2;	/* last two are jumps */

	क्रम (i = card->tst[0]; i < card->tst[0] + card->tst_size - 2; i++)
		ग_लिखो_sram(card, i, TSTE_OPC_VAR);
	ग_लिखो_sram(card, i++, TSTE_OPC_JMP | (card->tst[0] << 2));
	idt77252_sram_ग_लिखो_errors = 1;
	ग_लिखो_sram(card, i++, TSTE_OPC_JMP | (card->tst[1] << 2));
	idt77252_sram_ग_लिखो_errors = 0;
	क्रम (i = card->tst[1]; i < card->tst[1] + card->tst_size - 2; i++)
		ग_लिखो_sram(card, i, TSTE_OPC_VAR);
	ग_लिखो_sram(card, i++, TSTE_OPC_JMP | (card->tst[1] << 2));
	idt77252_sram_ग_लिखो_errors = 1;
	ग_लिखो_sram(card, i++, TSTE_OPC_JMP | (card->tst[0] << 2));
	idt77252_sram_ग_लिखो_errors = 0;

	card->tst_index = 0;
	ग_लिखोl(card->tst[0] << 2, SAR_REG_TSTB);

	/* Initialize ABRSTD and Receive FIFO */
	IPRINTK("%s: initialize ABRSTD ...\n", card->name);
	ग_लिखोl(card->abrst_size | (card->abrst_base << 2),
	       SAR_REG_ABRSTD);

	IPRINTK("%s: initialize receive fifo ...\n", card->name);
	ग_लिखोl(card->fअगरo_size | (card->fअगरo_base << 2),
	       SAR_REG_RXFD);

	IPRINTK("%s: SRAM initialization complete.\n", card->name);
पूर्ण

अटल पूर्णांक init_card(काष्ठा aपंचांग_dev *dev)
अणु
	काष्ठा idt77252_dev *card = dev->dev_data;
	काष्ठा pci_dev *pcidev = card->pcidev;
	अचिन्हित दीर्घ पंचांगpl, modl;
	अचिन्हित पूर्णांक linkrate, rsvdcr;
	अचिन्हित पूर्णांक tst_entries;
	काष्ठा net_device *पंचांगp;
	अक्षर tname[10];

	u32 size;
	u_अक्षर pci_byte;
	u32 conf;
	पूर्णांक i, k;

	अगर (test_bit(IDT77252_BIT_INIT, &card->flags)) अणु
		prपूर्णांकk("Error: SAR already initialized.\n");
		वापस -1;
	पूर्ण

/*****************************************************************/
/*   P C I   C O N F I G U R A T I O N                           */
/*****************************************************************/

	/* Set PCI Retry-Timeout and TRDY समयout */
	IPRINTK("%s: Checking PCI retries.\n", card->name);
	अगर (pci_पढ़ो_config_byte(pcidev, 0x40, &pci_byte) != 0) अणु
		prपूर्णांकk("%s: can't read PCI retry timeout.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	अगर (pci_byte != 0) अणु
		IPRINTK("%s: PCI retry timeout: %d, set to 0.\n",
			card->name, pci_byte);
		अगर (pci_ग_लिखो_config_byte(pcidev, 0x40, 0) != 0) अणु
			prपूर्णांकk("%s: can't set PCI retry timeout.\n",
			       card->name);
			deinit_card(card);
			वापस -1;
		पूर्ण
	पूर्ण
	IPRINTK("%s: Checking PCI TRDY.\n", card->name);
	अगर (pci_पढ़ो_config_byte(pcidev, 0x41, &pci_byte) != 0) अणु
		prपूर्णांकk("%s: can't read PCI TRDY timeout.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	अगर (pci_byte != 0) अणु
		IPRINTK("%s: PCI TRDY timeout: %d, set to 0.\n",
		        card->name, pci_byte);
		अगर (pci_ग_लिखो_config_byte(pcidev, 0x41, 0) != 0) अणु
			prपूर्णांकk("%s: can't set PCI TRDY timeout.\n", card->name);
			deinit_card(card);
			वापस -1;
		पूर्ण
	पूर्ण
	/* Reset Timer रेजिस्टर */
	अगर (पढ़ोl(SAR_REG_STAT) & SAR_STAT_TMROF) अणु
		prपूर्णांकk("%s: resetting timer overflow.\n", card->name);
		ग_लिखोl(SAR_STAT_TMROF, SAR_REG_STAT);
	पूर्ण
	IPRINTK("%s: Request IRQ ... ", card->name);
	अगर (request_irq(pcidev->irq, idt77252_पूर्णांकerrupt, IRQF_SHARED,
			card->name, card) != 0) अणु
		prपूर्णांकk("%s: can't allocate IRQ.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	IPRINTK("got %d.\n", pcidev->irq);

/*****************************************************************/
/*   C H E C K   A N D   I N I T   S R A M                       */
/*****************************************************************/

	IPRINTK("%s: Initializing SRAM\n", card->name);

	/* preset size of connecton table, so that init_sram() knows about it */
	conf =	SAR_CFG_TX_FIFO_SIZE_9 |	/* Use maximum fअगरo size */
		SAR_CFG_RXSTQ_SIZE_8k |		/* Receive Status Queue is 8k */
		SAR_CFG_IDLE_CLP |		/* Set CLP on idle cells */
#अगर_अघोषित ATM_IDT77252_SEND_IDLE
		SAR_CFG_NO_IDLE |		/* Do not send idle cells */
#पूर्ण_अगर
		0;

	अगर (card->sramsize == (512 * 1024))
		conf |= SAR_CFG_CNTBL_1k;
	अन्यथा
		conf |= SAR_CFG_CNTBL_512;

	चयन (vpibits) अणु
	हाल 0:
		conf |= SAR_CFG_VPVCS_0;
		अवरोध;
	शेष:
	हाल 1:
		conf |= SAR_CFG_VPVCS_1;
		अवरोध;
	हाल 2:
		conf |= SAR_CFG_VPVCS_2;
		अवरोध;
	हाल 8:
		conf |= SAR_CFG_VPVCS_8;
		अवरोध;
	पूर्ण

	ग_लिखोl(पढ़ोl(SAR_REG_CFG) | conf, SAR_REG_CFG);

	init_sram(card);

/********************************************************************/
/*  A L L O C   R A M   A N D   S E T   V A R I O U S   T H I N G S */
/********************************************************************/
	/* Initialize TSQ */
	अगर (0 != init_tsq(card)) अणु
		deinit_card(card);
		वापस -1;
	पूर्ण
	/* Initialize RSQ */
	अगर (0 != init_rsq(card)) अणु
		deinit_card(card);
		वापस -1;
	पूर्ण

	card->vpibits = vpibits;
	अगर (card->sramsize == (512 * 1024)) अणु
		card->vcibits = 10 - card->vpibits;
	पूर्ण अन्यथा अणु
		card->vcibits = 9 - card->vpibits;
	पूर्ण

	card->vcimask = 0;
	क्रम (k = 0, i = 1; k < card->vcibits; k++) अणु
		card->vcimask |= i;
		i <<= 1;
	पूर्ण

	IPRINTK("%s: Setting VPI/VCI mask to zero.\n", card->name);
	ग_लिखोl(0, SAR_REG_VPM);

	/* Little Endian Order   */
	ग_लिखोl(0, SAR_REG_GP);

	/* Initialize RAW Cell Handle Register  */
	card->raw_cell_hnd = dma_alloc_coherent(&card->pcidev->dev,
						2 * माप(u32),
						&card->raw_cell_paddr,
						GFP_KERNEL);
	अगर (!card->raw_cell_hnd) अणु
		prपूर्णांकk("%s: memory allocation failure.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	ग_लिखोl(card->raw_cell_paddr, SAR_REG_RAWHND);
	IPRINTK("%s: raw cell handle is at 0x%p.\n", card->name,
		card->raw_cell_hnd);

	size = माप(काष्ठा vc_map *) * card->tct_size;
	IPRINTK("%s: allocate %d byte for VC map.\n", card->name, size);
	card->vcs = vzalloc(size);
	अगर (!card->vcs) अणु
		prपूर्णांकk("%s: memory allocation failure.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण

	size = माप(काष्ठा vc_map *) * card->scd_size;
	IPRINTK("%s: allocate %d byte for SCD to VC mapping.\n",
	        card->name, size);
	card->scd2vc = vzalloc(size);
	अगर (!card->scd2vc) अणु
		prपूर्णांकk("%s: memory allocation failure.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण

	size = माप(काष्ठा tst_info) * (card->tst_size - 2);
	IPRINTK("%s: allocate %d byte for TST to VC mapping.\n",
		card->name, size);
	card->soft_tst = vदो_स्मृति(size);
	अगर (!card->soft_tst) अणु
		prपूर्णांकk("%s: memory allocation failure.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	क्रम (i = 0; i < card->tst_size - 2; i++) अणु
		card->soft_tst[i].tste = TSTE_OPC_VAR;
		card->soft_tst[i].vc = शून्य;
	पूर्ण

	अगर (dev->phy == शून्य) अणु
		prपूर्णांकk("%s: No LT device defined.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	अगर (dev->phy->ioctl == शून्य) अणु
		prपूर्णांकk("%s: LT had no IOCTL function defined.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण

#अगर_घोषित	CONFIG_ATM_IDT77252_USE_SUNI
	/*
	 * this is a jhs hack to get around special functionality in the
	 * phy driver क्रम the atecom hardware; the functionality करोesn't
	 * exist in the linux aपंचांग suni driver
	 *
	 * it isn't the right way to करो things, but as the guy from NIST
	 * said, talking about their measurement of the fine काष्ठाure
	 * स्थिरant, "it's good enough for government work."
	 */
	linkrate = 149760000;
#पूर्ण_अगर

	card->link_pcr = (linkrate / 8 / 53);
	prपूर्णांकk("%s: Linkrate on ATM line : %u bit/s, %u cell/s.\n",
	       card->name, linkrate, card->link_pcr);

#अगर_घोषित ATM_IDT77252_SEND_IDLE
	card->utopia_pcr = card->link_pcr;
#अन्यथा
	card->utopia_pcr = (160000000 / 8 / 54);
#पूर्ण_अगर

	rsvdcr = 0;
	अगर (card->utopia_pcr > card->link_pcr)
		rsvdcr = card->utopia_pcr - card->link_pcr;

	पंचांगpl = (अचिन्हित दीर्घ) rsvdcr * ((अचिन्हित दीर्घ) card->tst_size - 2);
	modl = पंचांगpl % (अचिन्हित दीर्घ)card->utopia_pcr;
	tst_entries = (पूर्णांक) (पंचांगpl / (अचिन्हित दीर्घ)card->utopia_pcr);
	अगर (modl)
		tst_entries++;
	card->tst_मुक्त -= tst_entries;
	fill_tst(card, शून्य, tst_entries, TSTE_OPC_शून्य);

#अगर_घोषित HAVE_EEPROM
	idt77252_eeprom_init(card);
	prपूर्णांकk("%s: EEPROM: %02x:", card->name,
		idt77252_eeprom_पढ़ो_status(card));

	क्रम (i = 0; i < 0x80; i++) अणु
		prपूर्णांकk(" %02x", 
		idt77252_eeprom_पढ़ो_byte(card, i)
		);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर /* HAVE_EEPROM */

	/*
	 * XXX: <hack>
	 */
	प्र_लिखो(tname, "eth%d", card->index);
	पंचांगp = dev_get_by_name(&init_net, tname);	/* jhs: was "tmp = dev_get(tname);" */
	अगर (पंचांगp) अणु
		स_नकल(card->aपंचांगdev->esi, पंचांगp->dev_addr, 6);
		dev_put(पंचांगp);
		prपूर्णांकk("%s: ESI %pM\n", card->name, card->aपंचांगdev->esi);
	पूर्ण
	/*
	 * XXX: </hack>
	 */

	/* Set Maximum Deficit Count क्रम now. */
	ग_लिखोl(0xffff, SAR_REG_MDFCT);

	set_bit(IDT77252_BIT_INIT, &card->flags);

	XPRINTK("%s: IDT77252 ABR SAR initialization complete.\n", card->name);
	वापस 0;
पूर्ण


/*****************************************************************************/
/*                                                                           */
/* Probing of IDT77252 ABR SAR                                               */
/*                                                                           */
/*****************************************************************************/


अटल पूर्णांक idt77252_preset(काष्ठा idt77252_dev *card)
अणु
	u16 pci_command;

/*****************************************************************/
/*   P C I   C O N F I G U R A T I O N                           */
/*****************************************************************/

	XPRINTK("%s: Enable PCI master and memory access for SAR.\n",
		card->name);
	अगर (pci_पढ़ो_config_word(card->pcidev, PCI_COMMAND, &pci_command)) अणु
		prपूर्णांकk("%s: can't read PCI_COMMAND.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
	अगर (!(pci_command & PCI_COMMAND_IO)) अणु
		prपूर्णांकk("%s: PCI_COMMAND: %04x (???)\n",
		       card->name, pci_command);
		deinit_card(card);
		वापस (-1);
	पूर्ण
	pci_command |= (PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER);
	अगर (pci_ग_लिखो_config_word(card->pcidev, PCI_COMMAND, pci_command)) अणु
		prपूर्णांकk("%s: can't write PCI_COMMAND.\n", card->name);
		deinit_card(card);
		वापस -1;
	पूर्ण
/*****************************************************************/
/*   G E N E R I C   R E S E T                                   */
/*****************************************************************/

	/* Software reset */
	ग_लिखोl(SAR_CFG_SWRST, SAR_REG_CFG);
	mdelay(1);
	ग_लिखोl(0, SAR_REG_CFG);

	IPRINTK("%s: Software resetted.\n", card->name);
	वापस 0;
पूर्ण


अटल अचिन्हित दीर्घ probe_sram(काष्ठा idt77252_dev *card)
अणु
	u32 data, addr;

	ग_लिखोl(0, SAR_REG_DR0);
	ग_लिखोl(SAR_CMD_WRITE_SRAM | (0 << 2), SAR_REG_CMD);

	क्रम (addr = 0x4000; addr < 0x80000; addr += 0x4000) अणु
		ग_लिखोl(ATM_POISON, SAR_REG_DR0);
		ग_लिखोl(SAR_CMD_WRITE_SRAM | (addr << 2), SAR_REG_CMD);

		ग_लिखोl(SAR_CMD_READ_SRAM | (0 << 2), SAR_REG_CMD);
		data = पढ़ोl(SAR_REG_DR0);

		अगर (data != 0)
			अवरोध;
	पूर्ण

	वापस addr * माप(u32);
पूर्ण

अटल पूर्णांक idt77252_init_one(काष्ठा pci_dev *pcidev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	अटल काष्ठा idt77252_dev **last = &idt77252_chain;
	अटल पूर्णांक index = 0;

	अचिन्हित दीर्घ membase, srambase;
	काष्ठा idt77252_dev *card;
	काष्ठा aपंचांग_dev *dev;
	पूर्णांक i, err;


	अगर ((err = pci_enable_device(pcidev))) अणु
		prपूर्णांकk("idt77252: can't enable PCI device at %s\n", pci_name(pcidev));
		वापस err;
	पूर्ण

	अगर ((err = dma_set_mask_and_coherent(&pcidev->dev, DMA_BIT_MASK(32)))) अणु
		prपूर्णांकk("idt77252: can't enable DMA for PCI device at %s\n", pci_name(pcidev));
		जाओ err_out_disable_pdev;
	पूर्ण

	card = kzalloc(माप(काष्ठा idt77252_dev), GFP_KERNEL);
	अगर (!card) अणु
		prपूर्णांकk("idt77252-%d: can't allocate private data\n", index);
		err = -ENOMEM;
		जाओ err_out_disable_pdev;
	पूर्ण
	card->revision = pcidev->revision;
	card->index = index;
	card->pcidev = pcidev;
	प्र_लिखो(card->name, "idt77252-%d", card->index);

	INIT_WORK(&card->tqueue, idt77252_softपूर्णांक);

	membase = pci_resource_start(pcidev, 1);
	srambase = pci_resource_start(pcidev, 2);

	mutex_init(&card->mutex);
	spin_lock_init(&card->cmd_lock);
	spin_lock_init(&card->tst_lock);

	समयr_setup(&card->tst_समयr, tst_समयr, 0);

	/* Do the I/O remapping... */
	card->membase = ioremap(membase, 1024);
	अगर (!card->membase) अणु
		prपूर्णांकk("%s: can't ioremap() membase\n", card->name);
		err = -EIO;
		जाओ err_out_मुक्त_card;
	पूर्ण

	अगर (idt77252_preset(card)) अणु
		prपूर्णांकk("%s: preset failed\n", card->name);
		err = -EIO;
		जाओ err_out_iounmap;
	पूर्ण

	dev = aपंचांग_dev_रेजिस्टर("idt77252", &pcidev->dev, &idt77252_ops, -1,
			       शून्य);
	अगर (!dev) अणु
		prपूर्णांकk("%s: can't register atm device\n", card->name);
		err = -EIO;
		जाओ err_out_iounmap;
	पूर्ण
	dev->dev_data = card;
	card->aपंचांगdev = dev;

#अगर_घोषित	CONFIG_ATM_IDT77252_USE_SUNI
	suni_init(dev);
	अगर (!dev->phy) अणु
		prपूर्णांकk("%s: can't init SUNI\n", card->name);
		err = -EIO;
		जाओ err_out_deinit_card;
	पूर्ण
#पूर्ण_अगर	/* CONFIG_ATM_IDT77252_USE_SUNI */

	card->sramsize = probe_sram(card);

	क्रम (i = 0; i < 4; i++) अणु
		card->fbq[i] = ioremap(srambase | 0x200000 | (i << 18), 4);
		अगर (!card->fbq[i]) अणु
			prपूर्णांकk("%s: can't ioremap() FBQ%d\n", card->name, i);
			err = -EIO;
			जाओ err_out_deinit_card;
		पूर्ण
	पूर्ण

	prपूर्णांकk("%s: ABR SAR (Rev %c): MEM %08lx SRAM %08lx [%u KB]\n",
	       card->name, ((card->revision > 1) && (card->revision < 25)) ?
	       'A' + card->revision - 1 : '?', membase, srambase,
	       card->sramsize / 1024);

	अगर (init_card(dev)) अणु
		prपूर्णांकk("%s: init_card failed\n", card->name);
		err = -EIO;
		जाओ err_out_deinit_card;
	पूर्ण

	dev->ci_range.vpi_bits = card->vpibits;
	dev->ci_range.vci_bits = card->vcibits;
	dev->link_rate = card->link_pcr;

	अगर (dev->phy->start)
		dev->phy->start(dev);

	अगर (idt77252_dev_खोलो(card)) अणु
		prपूर्णांकk("%s: dev_open failed\n", card->name);
		err = -EIO;
		जाओ err_out_stop;
	पूर्ण

	*last = card;
	last = &card->next;
	index++;

	वापस 0;

err_out_stop:
	अगर (dev->phy->stop)
		dev->phy->stop(dev);

err_out_deinit_card:
	deinit_card(card);

err_out_iounmap:
	iounmap(card->membase);

err_out_मुक्त_card:
	kमुक्त(card);

err_out_disable_pdev:
	pci_disable_device(pcidev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा pci_device_id idt77252_pci_tbl[] =
अणु
	अणु PCI_VDEVICE(IDT, PCI_DEVICE_ID_IDT_IDT77252), 0 पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, idt77252_pci_tbl);

अटल काष्ठा pci_driver idt77252_driver = अणु
	.name		= "idt77252",
	.id_table	= idt77252_pci_tbl,
	.probe		= idt77252_init_one,
पूर्ण;

अटल पूर्णांक __init idt77252_init(व्योम)
अणु
	काष्ठा sk_buff *skb;

	prपूर्णांकk("%s: at %p\n", __func__, idt77252_init);
	BUILD_BUG_ON(माप(skb->cb) < माप(काष्ठा idt77252_skb_prv) + माप(काष्ठा aपंचांग_skb_data));
	वापस pci_रेजिस्टर_driver(&idt77252_driver);
पूर्ण

अटल व्योम __निकास idt77252_निकास(व्योम)
अणु
	काष्ठा idt77252_dev *card;
	काष्ठा aपंचांग_dev *dev;

	pci_unरेजिस्टर_driver(&idt77252_driver);

	जबतक (idt77252_chain) अणु
		card = idt77252_chain;
		dev = card->aपंचांगdev;
		idt77252_chain = card->next;

		अगर (dev->phy->stop)
			dev->phy->stop(dev);
		deinit_card(card);
		pci_disable_device(card->pcidev);
		kमुक्त(card);
	पूर्ण

	DIPRINTK("idt77252: finished cleanup-module().\n");
पूर्ण

module_init(idt77252_init);
module_निकास(idt77252_निकास);

MODULE_LICENSE("GPL");

module_param(vpibits, uपूर्णांक, 0);
MODULE_PARM_DESC(vpibits, "number of VPI bits supported (0, 1, or 2)");
#अगर_घोषित CONFIG_ATM_IDT77252_DEBUG
module_param(debug, uदीर्घ, 0644);
MODULE_PARM_DESC(debug,   "debug bitmap, see drivers/atm/idt77252.h");
#पूर्ण_अगर

MODULE_AUTHOR("Eddie C. Dost <ecd@atecom.com>");
MODULE_DESCRIPTION("IDT77252 ABR SAR Driver");
