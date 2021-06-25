<शैली गुरु>
/* hermes.c
 *
 * Driver core क्रम the "Hermes" wireless MAC controller, as used in
 * the Lucent Orinoco and Cabletron RoamAbout cards. It should also
 * work on the hfa3841 and hfa3842 MAC controller chips used in the
 * Prism II chipsets.
 *
 * This is not a complete driver, just low-level access routines क्रम
 * the MAC controller itself.
 *
 * Based on the prism2 driver from Absolute Value Systems' linux-wlan
 * project, the Linux wvlan_cs driver, Lucent's HCF-Light
 * (wvlan_hcf.c) library, and the NetBSD wireless driver (in no
 * particular order).
 *
 * Copyright (C) 2000, David Gibson, Linuxcare Australia.
 * (C) Copyright David Gibson, IBM Corp. 2001-2003.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश "hermes.h"

/* These are maximum समयouts. Most often, card wil react much faster */
#घोषणा CMD_BUSY_TIMEOUT (100) /* In iterations of ~1us */
#घोषणा CMD_INIT_TIMEOUT (50000) /* in iterations of ~10us */
#घोषणा CMD_COMPL_TIMEOUT (20000) /* in iterations of ~10us */
#घोषणा ALLOC_COMPL_TIMEOUT (1000) /* in iterations of ~10us */

/*
 * AUX port access.  To unlock the AUX port ग_लिखो the access keys to the
 * PARAM0-2 रेजिस्टरs, then ग_लिखो HERMES_AUX_ENABLE to the HERMES_CONTROL
 * रेजिस्टर.  Then पढ़ो it and make sure it's HERMES_AUX_ENABLED.
 */
#घोषणा HERMES_AUX_ENABLE	0x8000	/* Enable auxiliary port access */
#घोषणा HERMES_AUX_DISABLE	0x4000	/* Disable to auxiliary port access */
#घोषणा HERMES_AUX_ENABLED	0xC000	/* Auxiliary port is खोलो */
#घोषणा HERMES_AUX_DISABLED	0x0000	/* Auxiliary port is बंदd */

#घोषणा HERMES_AUX_PW0	0xFE01
#घोषणा HERMES_AUX_PW1	0xDC23
#घोषणा HERMES_AUX_PW2	0xBA45

/* HERMES_CMD_DOWNLD */
#घोषणा HERMES_PROGRAM_DISABLE             (0x0000 | HERMES_CMD_DOWNLD)
#घोषणा HERMES_PROGRAM_ENABLE_VOLATILE     (0x0100 | HERMES_CMD_DOWNLD)
#घोषणा HERMES_PROGRAM_ENABLE_NON_VOLATILE (0x0200 | HERMES_CMD_DOWNLD)
#घोषणा HERMES_PROGRAM_NON_VOLATILE        (0x0300 | HERMES_CMD_DOWNLD)

/*
 * Debugging helpers
 */

#घोषणा DMSG(stuff...) करो अणुprपूर्णांकk(KERN_DEBUG "hermes @ %p: " , hw->iobase); \
			prपूर्णांकk(stuff); पूर्ण जबतक (0)

#अघोषित HERMES_DEBUG
#अगर_घोषित HERMES_DEBUG
#समावेश <मानकतर्क.स>

#घोषणा DEBUG(lvl, stuff...) अगर ((lvl) <= HERMES_DEBUG) DMSG(stuff)

#अन्यथा /* ! HERMES_DEBUG */

#घोषणा DEBUG(lvl, stuff...) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर /* ! HERMES_DEBUG */

अटल स्थिर काष्ठा hermes_ops hermes_ops_local;

/*
 * Internal functions
 */

/* Issue a command to the chip. Waiting क्रम it to complete is the caller's
   problem.

   Returns -EBUSY अगर the command रेजिस्टर is busy, 0 on success.

   Callable from any context.
*/
अटल पूर्णांक hermes_issue_cmd(काष्ठा hermes *hw, u16 cmd, u16 param0,
			    u16 param1, u16 param2)
अणु
	पूर्णांक k = CMD_BUSY_TIMEOUT;
	u16 reg;

	/* First रुको क्रम the command रेजिस्टर to unbusy */
	reg = hermes_पढ़ो_regn(hw, CMD);
	जबतक ((reg & HERMES_CMD_BUSY) && k) अणु
		k--;
		udelay(1);
		reg = hermes_पढ़ो_regn(hw, CMD);
	पूर्ण
	अगर (reg & HERMES_CMD_BUSY)
		वापस -EBUSY;

	hermes_ग_लिखो_regn(hw, PARAM2, param2);
	hermes_ग_लिखो_regn(hw, PARAM1, param1);
	hermes_ग_लिखो_regn(hw, PARAM0, param0);
	hermes_ग_लिखो_regn(hw, CMD, cmd);

	वापस 0;
पूर्ण

/*
 * Function definitions
 */

/* For करोing cmds that wipe the magic स्थिरant in SWSUPPORT0 */
अटल पूर्णांक hermes_करोicmd_रुको(काष्ठा hermes *hw, u16 cmd,
			      u16 parm0, u16 parm1, u16 parm2,
			      काष्ठा hermes_response *resp)
अणु
	पूर्णांक err = 0;
	पूर्णांक k;
	u16 status, reg;

	err = hermes_issue_cmd(hw, cmd, parm0, parm1, parm2);
	अगर (err)
		वापस err;

	reg = hermes_पढ़ो_regn(hw, EVSTAT);
	k = CMD_INIT_TIMEOUT;
	जबतक ((!(reg & HERMES_EV_CMD)) && k) अणु
		k--;
		udelay(10);
		reg = hermes_पढ़ो_regn(hw, EVSTAT);
	पूर्ण

	hermes_ग_लिखो_regn(hw, SWSUPPORT0, HERMES_MAGIC);

	अगर (!hermes_present(hw)) अणु
		DEBUG(0, "hermes @ 0x%x: Card removed during reset.\n",
		       hw->iobase);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!(reg & HERMES_EV_CMD)) अणु
		prपूर्णांकk(KERN_ERR "hermes @ %p: "
		       "Timeout waiting for card to reset (reg=0x%04x)!\n",
		       hw->iobase, reg);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	status = hermes_पढ़ो_regn(hw, STATUS);
	अगर (resp) अणु
		resp->status = status;
		resp->resp0 = hermes_पढ़ो_regn(hw, RESP0);
		resp->resp1 = hermes_पढ़ो_regn(hw, RESP1);
		resp->resp2 = hermes_पढ़ो_regn(hw, RESP2);
	पूर्ण

	hermes_ग_लिखो_regn(hw, EVACK, HERMES_EV_CMD);

	अगर (status & HERMES_STATUS_RESULT)
		err = -EIO;
out:
	वापस err;
पूर्ण

व्योम hermes_काष्ठा_init(काष्ठा hermes *hw, व्योम __iomem *address,
			पूर्णांक reg_spacing)
अणु
	hw->iobase = address;
	hw->reg_spacing = reg_spacing;
	hw->पूर्णांकen = 0x0;
	hw->eeprom_pda = false;
	hw->ops = &hermes_ops_local;
पूर्ण
EXPORT_SYMBOL(hermes_काष्ठा_init);

अटल पूर्णांक hermes_init(काष्ठा hermes *hw)
अणु
	u16 reg;
	पूर्णांक err = 0;
	पूर्णांक k;

	/* We करोn't want to be पूर्णांकerrupted जबतक resetting the chipset */
	hw->पूर्णांकen = 0x0;
	hermes_ग_लिखो_regn(hw, INTEN, 0);
	hermes_ग_लिखो_regn(hw, EVACK, 0xffff);

	/* Normally it's a "can't happen" क्रम the command रेजिस्टर to
	   be busy when we go to issue a command because we are
	   serializing all commands.  However we want to have some
	   chance of resetting the card even अगर it माला_लो पूर्णांकo a stupid
	   state, so we actually रुको to see अगर the command रेजिस्टर
	   will unbusy itself here. */
	k = CMD_BUSY_TIMEOUT;
	reg = hermes_पढ़ो_regn(hw, CMD);
	जबतक (k && (reg & HERMES_CMD_BUSY)) अणु
		अगर (reg == 0xffff) /* Special हाल - the card has probably been
				      हटाओd, so करोn't रुको क्रम the समयout */
			वापस -ENODEV;

		k--;
		udelay(1);
		reg = hermes_पढ़ो_regn(hw, CMD);
	पूर्ण

	/* No need to explicitly handle the समयout - अगर we've समयd
	   out hermes_issue_cmd() will probably वापस -EBUSY below */

	/* According to the करोcumentation, EVSTAT may contain
	   obsolete event occurrence inक्रमmation.  We have to acknowledge
	   it by writing EVACK. */
	reg = hermes_पढ़ो_regn(hw, EVSTAT);
	hermes_ग_लिखो_regn(hw, EVACK, reg);

	/* We करोn't use hermes_करोcmd_रुको here, because the reset wipes
	   the magic स्थिरant in SWSUPPORT0 away, and it माला_लो confused */
	err = hermes_करोicmd_रुको(hw, HERMES_CMD_INIT, 0, 0, 0, शून्य);

	वापस err;
पूर्ण

/* Issue a command to the chip, and (busy!) रुको क्रम it to
 * complete.
 *
 * Returns:
 *     < 0 on पूर्णांकernal error
 *       0 on success
 *     > 0 on error वापसed by the firmware
 *
 * Callable from any context, but locking is your problem. */
अटल पूर्णांक hermes_करोcmd_रुको(काष्ठा hermes *hw, u16 cmd, u16 parm0,
			     काष्ठा hermes_response *resp)
अणु
	पूर्णांक err;
	पूर्णांक k;
	u16 reg;
	u16 status;

	err = hermes_issue_cmd(hw, cmd, parm0, 0, 0);
	अगर (err) अणु
		अगर (!hermes_present(hw)) अणु
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_WARNING "hermes @ %p: "
				       "Card removed while issuing command "
				       "0x%04x.\n", hw->iobase, cmd);
			err = -ENODEV;
		पूर्ण अन्यथा
			अगर (net_ratelimit())
				prपूर्णांकk(KERN_ERR "hermes @ %p: "
				       "Error %d issuing command 0x%04x.\n",
				       hw->iobase, err, cmd);
		जाओ out;
	पूर्ण

	reg = hermes_पढ़ो_regn(hw, EVSTAT);
	k = CMD_COMPL_TIMEOUT;
	जबतक ((!(reg & HERMES_EV_CMD)) && k) अणु
		k--;
		udelay(10);
		reg = hermes_पढ़ो_regn(hw, EVSTAT);
	पूर्ण

	अगर (!hermes_present(hw)) अणु
		prपूर्णांकk(KERN_WARNING "hermes @ %p: Card removed "
		       "while waiting for command 0x%04x completion.\n",
		       hw->iobase, cmd);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!(reg & HERMES_EV_CMD)) अणु
		prपूर्णांकk(KERN_ERR "hermes @ %p: Timeout waiting for "
		       "command 0x%04x completion.\n", hw->iobase, cmd);
		err = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	status = hermes_पढ़ो_regn(hw, STATUS);
	अगर (resp) अणु
		resp->status = status;
		resp->resp0 = hermes_पढ़ो_regn(hw, RESP0);
		resp->resp1 = hermes_पढ़ो_regn(hw, RESP1);
		resp->resp2 = hermes_पढ़ो_regn(hw, RESP2);
	पूर्ण

	hermes_ग_लिखो_regn(hw, EVACK, HERMES_EV_CMD);

	अगर (status & HERMES_STATUS_RESULT)
		err = -EIO;

 out:
	वापस err;
पूर्ण

अटल पूर्णांक hermes_allocate(काष्ठा hermes *hw, u16 size, u16 *fid)
अणु
	पूर्णांक err = 0;
	पूर्णांक k;
	u16 reg;

	अगर ((size < HERMES_ALLOC_LEN_MIN) || (size > HERMES_ALLOC_LEN_MAX))
		वापस -EINVAL;

	err = hermes_करोcmd_रुको(hw, HERMES_CMD_ALLOC, size, शून्य);
	अगर (err)
		वापस err;

	reg = hermes_पढ़ो_regn(hw, EVSTAT);
	k = ALLOC_COMPL_TIMEOUT;
	जबतक ((!(reg & HERMES_EV_ALLOC)) && k) अणु
		k--;
		udelay(10);
		reg = hermes_पढ़ो_regn(hw, EVSTAT);
	पूर्ण

	अगर (!hermes_present(hw)) अणु
		prपूर्णांकk(KERN_WARNING "hermes @ %p: "
		       "Card removed waiting for frame allocation.\n",
		       hw->iobase);
		वापस -ENODEV;
	पूर्ण

	अगर (!(reg & HERMES_EV_ALLOC)) अणु
		prपूर्णांकk(KERN_ERR "hermes @ %p: "
		       "Timeout waiting for frame allocation\n",
		       hw->iobase);
		वापस -ETIMEDOUT;
	पूर्ण

	*fid = hermes_पढ़ो_regn(hw, ALLOCFID);
	hermes_ग_लिखो_regn(hw, EVACK, HERMES_EV_ALLOC);

	वापस 0;
पूर्ण

/* Set up a BAP to पढ़ो a particular chunk of data from card's पूर्णांकernal buffer.
 *
 * Returns:
 *     < 0 on पूर्णांकernal failure (त्रुटि_सं)
 *       0 on success
 *     > 0 on error
 * from firmware
 *
 * Callable from any context */
अटल पूर्णांक hermes_bap_seek(काष्ठा hermes *hw, पूर्णांक bap, u16 id, u16 offset)
अणु
	पूर्णांक sreg = bap ? HERMES_SELECT1 : HERMES_SELECT0;
	पूर्णांक oreg = bap ? HERMES_OFFSET1 : HERMES_OFFSET0;
	पूर्णांक k;
	u16 reg;

	/* Paranoia.. */
	अगर ((offset > HERMES_BAP_OFFSET_MAX) || (offset % 2))
		वापस -EINVAL;

	k = HERMES_BAP_BUSY_TIMEOUT;
	reg = hermes_पढ़ो_reg(hw, oreg);
	जबतक ((reg & HERMES_OFFSET_BUSY) && k) अणु
		k--;
		udelay(1);
		reg = hermes_पढ़ो_reg(hw, oreg);
	पूर्ण

	अगर (reg & HERMES_OFFSET_BUSY)
		वापस -ETIMEDOUT;

	/* Now we actually set up the transfer */
	hermes_ग_लिखो_reg(hw, sreg, id);
	hermes_ग_लिखो_reg(hw, oreg, offset);

	/* Wait क्रम the BAP to be पढ़ोy */
	k = HERMES_BAP_BUSY_TIMEOUT;
	reg = hermes_पढ़ो_reg(hw, oreg);
	जबतक ((reg & (HERMES_OFFSET_BUSY | HERMES_OFFSET_ERR)) && k) अणु
		k--;
		udelay(1);
		reg = hermes_पढ़ो_reg(hw, oreg);
	पूर्ण

	अगर (reg != offset) अणु
		prपूर्णांकk(KERN_ERR "hermes @ %p: BAP%d offset %s: "
		       "reg=0x%x id=0x%x offset=0x%x\n", hw->iobase, bap,
		       (reg & HERMES_OFFSET_BUSY) ? "timeout" : "error",
		       reg, id, offset);

		अगर (reg & HERMES_OFFSET_BUSY)
			वापस -ETIMEDOUT;

		वापस -EIO;		/* error or wrong offset */
	पूर्ण

	वापस 0;
पूर्ण

/* Read a block of data from the chip's buffer, via the
 * BAP. Synchronization/serialization is the caller's problem.  len
 * must be even.
 *
 * Returns:
 *     < 0 on पूर्णांकernal failure (त्रुटि_सं)
 *       0 on success
 *     > 0 on error from firmware
 */
अटल पूर्णांक hermes_bap_pपढ़ो(काष्ठा hermes *hw, पूर्णांक bap, व्योम *buf, पूर्णांक len,
			    u16 id, u16 offset)
अणु
	पूर्णांक dreg = bap ? HERMES_DATA1 : HERMES_DATA0;
	पूर्णांक err = 0;

	अगर ((len < 0) || (len % 2))
		वापस -EINVAL;

	err = hermes_bap_seek(hw, bap, id, offset);
	अगर (err)
		जाओ out;

	/* Actually करो the transfer */
	hermes_पढ़ो_words(hw, dreg, buf, len / 2);

 out:
	वापस err;
पूर्ण

/* Write a block of data to the chip's buffer, via the
 * BAP. Synchronization/serialization is the caller's problem.
 *
 * Returns:
 *     < 0 on पूर्णांकernal failure (त्रुटि_सं)
 *       0 on success
 *     > 0 on error from firmware
 */
अटल पूर्णांक hermes_bap_pग_लिखो(काष्ठा hermes *hw, पूर्णांक bap, स्थिर व्योम *buf,
			     पूर्णांक len, u16 id, u16 offset)
अणु
	पूर्णांक dreg = bap ? HERMES_DATA1 : HERMES_DATA0;
	पूर्णांक err = 0;

	अगर (len < 0)
		वापस -EINVAL;

	err = hermes_bap_seek(hw, bap, id, offset);
	अगर (err)
		जाओ out;

	/* Actually करो the transfer */
	hermes_ग_लिखो_bytes(hw, dreg, buf, len);

 out:
	वापस err;
पूर्ण

/* Read a Length-Type-Value record from the card.
 *
 * If length is शून्य, we ignore the length पढ़ो from the card, and
 * पढ़ो the entire buffer regardless. This is useful because some of
 * the configuration records appear to have incorrect lengths in
 * practice.
 *
 * Callable from user or bh context.  */
अटल पूर्णांक hermes_पढ़ो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			   अचिन्हित bufsize, u16 *length, व्योम *buf)
अणु
	पूर्णांक err = 0;
	पूर्णांक dreg = bap ? HERMES_DATA1 : HERMES_DATA0;
	u16 rlength, rtype;
	अचिन्हित nwords;

	अगर (bufsize % 2)
		वापस -EINVAL;

	err = hermes_करोcmd_रुको(hw, HERMES_CMD_ACCESS, rid, शून्य);
	अगर (err)
		वापस err;

	err = hermes_bap_seek(hw, bap, rid, 0);
	अगर (err)
		वापस err;

	rlength = hermes_पढ़ो_reg(hw, dreg);

	अगर (!rlength)
		वापस -ENODATA;

	rtype = hermes_पढ़ो_reg(hw, dreg);

	अगर (length)
		*length = rlength;

	अगर (rtype != rid)
		prपूर्णांकk(KERN_WARNING "hermes @ %p: %s(): "
		       "rid (0x%04x) does not match type (0x%04x)\n",
		       hw->iobase, __func__, rid, rtype);
	अगर (HERMES_RECLEN_TO_BYTES(rlength) > bufsize)
		prपूर्णांकk(KERN_WARNING "hermes @ %p: "
		       "Truncating LTV record from %d to %d bytes. "
		       "(rid=0x%04x, len=0x%04x)\n", hw->iobase,
		       HERMES_RECLEN_TO_BYTES(rlength), bufsize, rid, rlength);

	nwords = min((अचिन्हित)rlength - 1, bufsize / 2);
	hermes_पढ़ो_words(hw, dreg, buf, nwords);

	वापस 0;
पूर्ण

अटल पूर्णांक hermes_ग_लिखो_ltv(काष्ठा hermes *hw, पूर्णांक bap, u16 rid,
			    u16 length, स्थिर व्योम *value)
अणु
	पूर्णांक dreg = bap ? HERMES_DATA1 : HERMES_DATA0;
	पूर्णांक err = 0;
	अचिन्हित count;

	अगर (length == 0)
		वापस -EINVAL;

	err = hermes_bap_seek(hw, bap, rid, 0);
	अगर (err)
		वापस err;

	hermes_ग_लिखो_reg(hw, dreg, length);
	hermes_ग_लिखो_reg(hw, dreg, rid);

	count = length - 1;

	hermes_ग_लिखो_bytes(hw, dreg, value, count << 1);

	err = hermes_करोcmd_रुको(hw, HERMES_CMD_ACCESS | HERMES_CMD_WRITE,
				rid, शून्य);

	वापस err;
पूर्ण

/*** Hermes AUX control ***/

अटल अंतरभूत व्योम
hermes_aux_setaddr(काष्ठा hermes *hw, u32 addr)
अणु
	hermes_ग_लिखो_reg(hw, HERMES_AUXPAGE, (u16) (addr >> 7));
	hermes_ग_लिखो_reg(hw, HERMES_AUXOFFSET, (u16) (addr & 0x7F));
पूर्ण

अटल अंतरभूत पूर्णांक
hermes_aux_control(काष्ठा hermes *hw, पूर्णांक enabled)
अणु
	पूर्णांक desired_state = enabled ? HERMES_AUX_ENABLED : HERMES_AUX_DISABLED;
	पूर्णांक action = enabled ? HERMES_AUX_ENABLE : HERMES_AUX_DISABLE;
	पूर्णांक i;

	/* Alपढ़ोy खोलो? */
	अगर (hermes_पढ़ो_reg(hw, HERMES_CONTROL) == desired_state)
		वापस 0;

	hermes_ग_लिखो_reg(hw, HERMES_PARAM0, HERMES_AUX_PW0);
	hermes_ग_लिखो_reg(hw, HERMES_PARAM1, HERMES_AUX_PW1);
	hermes_ग_लिखो_reg(hw, HERMES_PARAM2, HERMES_AUX_PW2);
	hermes_ग_लिखो_reg(hw, HERMES_CONTROL, action);

	क्रम (i = 0; i < 20; i++) अणु
		udelay(10);
		अगर (hermes_पढ़ो_reg(hw, HERMES_CONTROL) ==
		    desired_state)
			वापस 0;
	पूर्ण

	वापस -EBUSY;
पूर्ण

/*** Hermes programming ***/

/* About to start programming data (Hermes I)
 * offset is the entry poपूर्णांक
 *
 * Spectrum_cs' Symbol fw करोes not require this
 * wl_lkm Agere fw करोes
 * Don't know about पूर्णांकersil
 */
अटल पूर्णांक hermesi_program_init(काष्ठा hermes *hw, u32 offset)
अणु
	पूर्णांक err;

	/* Disable पूर्णांकerrupts?*/
	/*hw->पूर्णांकen = 0x0;*/
	/*hermes_ग_लिखो_regn(hw, INTEN, 0);*/
	/*hermes_set_irqmask(hw, 0);*/

	/* Acknowledge any outstanding command */
	hermes_ग_लिखो_regn(hw, EVACK, 0xFFFF);

	/* Using init_cmd_रुको rather than cmd_रुको */
	err = hw->ops->init_cmd_रुको(hw,
				     0x0100 | HERMES_CMD_INIT,
				     0, 0, 0, शून्य);
	अगर (err)
		वापस err;

	err = hw->ops->init_cmd_रुको(hw,
				     0x0000 | HERMES_CMD_INIT,
				     0, 0, 0, शून्य);
	अगर (err)
		वापस err;

	err = hermes_aux_control(hw, 1);
	pr_debug("AUX enable returned %d\n", err);

	अगर (err)
		वापस err;

	pr_debug("Enabling volatile, EP 0x%08x\n", offset);
	err = hw->ops->init_cmd_रुको(hw,
				     HERMES_PROGRAM_ENABLE_VOLATILE,
				     offset & 0xFFFFu,
				     offset >> 16,
				     0,
				     शून्य);
	pr_debug("PROGRAM_ENABLE returned %d\n", err);

	वापस err;
पूर्ण

/* Done programming data (Hermes I)
 *
 * Spectrum_cs' Symbol fw करोes not require this
 * wl_lkm Agere fw करोes
 * Don't know about पूर्णांकersil
 */
अटल पूर्णांक hermesi_program_end(काष्ठा hermes *hw)
अणु
	काष्ठा hermes_response resp;
	पूर्णांक rc = 0;
	पूर्णांक err;

	rc = hw->ops->cmd_रुको(hw, HERMES_PROGRAM_DISABLE, 0, &resp);

	pr_debug("PROGRAM_DISABLE returned %d, "
		 "r0 0x%04x, r1 0x%04x, r2 0x%04x\n",
		 rc, resp.resp0, resp.resp1, resp.resp2);

	अगर ((rc == 0) &&
	    ((resp.status & HERMES_STATUS_CMDCODE) != HERMES_CMD_DOWNLD))
		rc = -EIO;

	err = hermes_aux_control(hw, 0);
	pr_debug("AUX disable returned %d\n", err);

	/* Acknowledge any outstanding command */
	hermes_ग_लिखो_regn(hw, EVACK, 0xFFFF);

	/* Reinitialise, ignoring वापस */
	(व्योम) hw->ops->init_cmd_रुको(hw, 0x0000 | HERMES_CMD_INIT,
				      0, 0, 0, शून्य);

	वापस rc ? rc : err;
पूर्ण

अटल पूर्णांक hermes_program_bytes(काष्ठा hermes *hw, स्थिर अक्षर *data,
				u32 addr, u32 len)
अणु
	/* wl lkm splits the programming पूर्णांकo chunks of 2000 bytes.
	 * This restriction appears to come from USB. The PCMCIA
	 * adapters can program the whole lot in one go */
	hermes_aux_setaddr(hw, addr);
	hermes_ग_लिखो_bytes(hw, HERMES_AUXDATA, data, len);
	वापस 0;
पूर्ण

/* Read PDA from the adapter */
अटल पूर्णांक hermes_पढ़ो_pda(काष्ठा hermes *hw, __le16 *pda, u32 pda_addr,
			   u16 pda_len)
अणु
	पूर्णांक ret;
	u16 pda_size;
	u16 data_len = pda_len;
	__le16 *data = pda;

	अगर (hw->eeprom_pda) अणु
		/* PDA of spectrum symbol is in eeprom */

		/* Issue command to पढ़ो EEPROM */
		ret = hw->ops->cmd_रुको(hw, HERMES_CMD_READMIF, 0, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* wl_lkm करोes not include PDA size in the PDA area.
		 * We will pad the inक्रमmation पूर्णांकo pda, so other routines
		 * करोn't have to be modअगरied */
		pda[0] = cpu_to_le16(pda_len - 2);
			/* Includes CFG_PROD_DATA but not itself */
		pda[1] = cpu_to_le16(0x0800); /* CFG_PROD_DATA */
		data_len = pda_len - 4;
		data = pda + 2;
	पूर्ण

	/* Open auxiliary port */
	ret = hermes_aux_control(hw, 1);
	pr_debug("AUX enable returned %d\n", ret);
	अगर (ret)
		वापस ret;

	/* Read PDA */
	hermes_aux_setaddr(hw, pda_addr);
	hermes_पढ़ो_words(hw, HERMES_AUXDATA, data, data_len / 2);

	/* Close aux port */
	ret = hermes_aux_control(hw, 0);
	pr_debug("AUX disable returned %d\n", ret);

	/* Check PDA length */
	pda_size = le16_to_cpu(pda[0]);
	pr_debug("Actual PDA length %d, Max allowed %d\n",
		 pda_size, pda_len);
	अगर (pda_size > pda_len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम hermes_lock_irqsave(spinlock_t *lock,
				अचिन्हित दीर्घ *flags) __acquires(lock)
अणु
	spin_lock_irqsave(lock, *flags);
पूर्ण

अटल व्योम hermes_unlock_irqrestore(spinlock_t *lock,
				     अचिन्हित दीर्घ *flags) __releases(lock)
अणु
	spin_unlock_irqrestore(lock, *flags);
पूर्ण

अटल व्योम hermes_lock_irq(spinlock_t *lock) __acquires(lock)
अणु
	spin_lock_irq(lock);
पूर्ण

अटल व्योम hermes_unlock_irq(spinlock_t *lock) __releases(lock)
अणु
	spin_unlock_irq(lock);
पूर्ण

/* Hermes operations क्रम local buses */
अटल स्थिर काष्ठा hermes_ops hermes_ops_local = अणु
	.init = hermes_init,
	.cmd_रुको = hermes_करोcmd_रुको,
	.init_cmd_रुको = hermes_करोicmd_रुको,
	.allocate = hermes_allocate,
	.पढ़ो_ltv = hermes_पढ़ो_ltv,
	.पढ़ो_ltv_pr = hermes_पढ़ो_ltv,
	.ग_लिखो_ltv = hermes_ग_लिखो_ltv,
	.bap_pपढ़ो = hermes_bap_pपढ़ो,
	.bap_pग_लिखो = hermes_bap_pग_लिखो,
	.पढ़ो_pda = hermes_पढ़ो_pda,
	.program_init = hermesi_program_init,
	.program_end = hermesi_program_end,
	.program = hermes_program_bytes,
	.lock_irqsave = hermes_lock_irqsave,
	.unlock_irqrestore = hermes_unlock_irqrestore,
	.lock_irq = hermes_lock_irq,
	.unlock_irq = hermes_unlock_irq,
पूर्ण;
