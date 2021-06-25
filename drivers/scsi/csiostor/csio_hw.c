<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/pci.h>
#समावेश <linux/pci_regs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/delay.h>
#समावेश <linux/माला.स>
#समावेश <linux/compiler.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>

#समावेश "csio_hw.h"
#समावेश "csio_lnode.h"
#समावेश "csio_rnode.h"

पूर्णांक csio_dbg_level = 0xFEFF;
अचिन्हित पूर्णांक csio_port_mask = 0xf;

/* Default FW event queue entries. */
अटल uपूर्णांक32_t csio_evtq_sz = CSIO_EVTQ_SIZE;

/* Default MSI param level */
पूर्णांक csio_msi = 2;

/* FCoE function instances */
अटल पूर्णांक dev_num;

/* FCoE Adapter types & its description */
अटल स्थिर काष्ठा csio_adap_desc csio_t5_fcoe_adapters[] = अणु
	अणु"T580-Dbg 10G", "Chelsio T580-Dbg 10G [FCoE]"पूर्ण,
	अणु"T520-CR 10G", "Chelsio T520-CR 10G [FCoE]"पूर्ण,
	अणु"T522-CR 10G/1G", "Chelsio T522-CR 10G/1G [FCoE]"पूर्ण,
	अणु"T540-CR 10G", "Chelsio T540-CR 10G [FCoE]"पूर्ण,
	अणु"T520-BCH 10G", "Chelsio T520-BCH 10G [FCoE]"पूर्ण,
	अणु"T540-BCH 10G", "Chelsio T540-BCH 10G [FCoE]"पूर्ण,
	अणु"T540-CH 10G", "Chelsio T540-CH 10G [FCoE]"पूर्ण,
	अणु"T520-SO 10G", "Chelsio T520-SO 10G [FCoE]"पूर्ण,
	अणु"T520-CX4 10G", "Chelsio T520-CX4 10G [FCoE]"पूर्ण,
	अणु"T520-BT 10G", "Chelsio T520-BT 10G [FCoE]"पूर्ण,
	अणु"T504-BT 1G", "Chelsio T504-BT 1G [FCoE]"पूर्ण,
	अणु"B520-SR 10G", "Chelsio B520-SR 10G [FCoE]"पूर्ण,
	अणु"B504-BT 1G", "Chelsio B504-BT 1G [FCoE]"पूर्ण,
	अणु"T580-CR 10G", "Chelsio T580-CR 10G [FCoE]"पूर्ण,
	अणु"T540-LP-CR 10G", "Chelsio T540-LP-CR 10G [FCoE]"पूर्ण,
	अणु"AMSTERDAM 10G", "Chelsio AMSTERDAM 10G [FCoE]"पूर्ण,
	अणु"T580-LP-CR 40G", "Chelsio T580-LP-CR 40G [FCoE]"पूर्ण,
	अणु"T520-LL-CR 10G", "Chelsio T520-LL-CR 10G [FCoE]"पूर्ण,
	अणु"T560-CR 40G", "Chelsio T560-CR 40G [FCoE]"पूर्ण,
	अणु"T580-CR 40G", "Chelsio T580-CR 40G [FCoE]"पूर्ण,
	अणु"T580-SO 40G", "Chelsio T580-SO 40G [FCoE]"पूर्ण,
	अणु"T502-BT 1G", "Chelsio T502-BT 1G [FCoE]"पूर्ण
पूर्ण;

अटल व्योम csio_mgmपंचांग_cleanup(काष्ठा csio_mgmपंचांग *);
अटल व्योम csio_hw_mbm_cleanup(काष्ठा csio_hw *);

/* State machine क्रमward declarations */
अटल व्योम csio_hws_uninit(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_configuring(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_initializing(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_पढ़ोy(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_quiescing(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_quiesced(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_resetting(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_removing(काष्ठा csio_hw *, क्रमागत csio_hw_ev);
अटल व्योम csio_hws_pcierr(काष्ठा csio_hw *, क्रमागत csio_hw_ev);

अटल व्योम csio_hw_initialize(काष्ठा csio_hw *hw);
अटल व्योम csio_evtq_stop(काष्ठा csio_hw *hw);
अटल व्योम csio_evtq_start(काष्ठा csio_hw *hw);

पूर्णांक csio_is_hw_पढ़ोy(काष्ठा csio_hw *hw)
अणु
	वापस csio_match_state(hw, csio_hws_पढ़ोy);
पूर्ण

पूर्णांक csio_is_hw_removing(काष्ठा csio_hw *hw)
अणु
	वापस csio_match_state(hw, csio_hws_removing);
पूर्ण


/*
 *	csio_hw_रुको_op_करोne_val - रुको until an operation is completed
 *	@hw: the HW module
 *	@reg: the रेजिस्टर to check क्रम completion
 *	@mask: a single-bit field within @reg that indicates completion
 *	@polarity: the value of the field when the operation is completed
 *	@attempts: number of check iterations
 *	@delay: delay in usecs between iterations
 *	@valp: where to store the value of the रेजिस्टर at completion समय
 *
 *	Wait until an operation is completed by checking a bit in a रेजिस्टर
 *	up to @attempts बार.  If @valp is not शून्य the value of the रेजिस्टर
 *	at the समय it indicated completion is stored there.  Returns 0 अगर the
 *	operation completes and	-EAGAIN	otherwise.
 */
पूर्णांक
csio_hw_रुको_op_करोne_val(काष्ठा csio_hw *hw, पूर्णांक reg, uपूर्णांक32_t mask,
			 पूर्णांक polarity, पूर्णांक attempts, पूर्णांक delay, uपूर्णांक32_t *valp)
अणु
	uपूर्णांक32_t val;
	जबतक (1) अणु
		val = csio_rd_reg32(hw, reg);

		अगर (!!(val & mask) == polarity) अणु
			अगर (valp)
				*valp = val;
			वापस 0;
		पूर्ण

		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			udelay(delay);
	पूर्ण
पूर्ण

/*
 *	csio_hw_tp_wr_bits_indirect - set/clear bits in an indirect TP रेजिस्टर
 *	@hw: the adapter
 *	@addr: the indirect TP रेजिस्टर address
 *	@mask: specअगरies the field within the रेजिस्टर to modअगरy
 *	@val: new value क्रम the field
 *
 *	Sets a field of an indirect TP रेजिस्टर to the given value.
 */
व्योम
csio_hw_tp_wr_bits_indirect(काष्ठा csio_hw *hw, अचिन्हित पूर्णांक addr,
			अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	csio_wr_reg32(hw, addr, TP_PIO_ADDR_A);
	val |= csio_rd_reg32(hw, TP_PIO_DATA_A) & ~mask;
	csio_wr_reg32(hw, val, TP_PIO_DATA_A);
पूर्ण

व्योम
csio_set_reg_field(काष्ठा csio_hw *hw, uपूर्णांक32_t reg, uपूर्णांक32_t mask,
		   uपूर्णांक32_t value)
अणु
	uपूर्णांक32_t val = csio_rd_reg32(hw, reg) & ~mask;

	csio_wr_reg32(hw, val | value, reg);
	/* Flush */
	csio_rd_reg32(hw, reg);

पूर्ण

अटल पूर्णांक
csio_memory_ग_लिखो(काष्ठा csio_hw *hw, पूर्णांक mtype, u32 addr, u32 len, u32 *buf)
अणु
	वापस hw->chip_ops->chip_memory_rw(hw, MEMWIN_CSIOSTOR, mtype,
					    addr, len, buf, 0);
पूर्ण

/*
 * EEPROM पढ़ोs take a few tens of us जबतक ग_लिखोs can take a bit over 5 ms.
 */
#घोषणा EEPROM_MAX_RD_POLL	40
#घोषणा EEPROM_MAX_WR_POLL	6
#घोषणा EEPROM_STAT_ADDR	0x7bfc
#घोषणा VPD_BASE		0x400
#घोषणा VPD_BASE_OLD		0
#घोषणा VPD_LEN			1024
#घोषणा VPD_INFO_FLD_HDR_SIZE	3

/*
 *	csio_hw_seeprom_पढ़ो - पढ़ो a serial EEPROM location
 *	@hw: hw to पढ़ो
 *	@addr: EEPROM भव address
 *	@data: where to store the पढ़ो data
 *
 *	Read a 32-bit word from a location in serial EEPROM using the card's PCI
 *	VPD capability.  Note that this function must be called with a भव
 *	address.
 */
अटल पूर्णांक
csio_hw_seeprom_पढ़ो(काष्ठा csio_hw *hw, uपूर्णांक32_t addr, uपूर्णांक32_t *data)
अणु
	uपूर्णांक16_t val = 0;
	पूर्णांक attempts = EEPROM_MAX_RD_POLL;
	uपूर्णांक32_t base = hw->params.pci.vpd_cap_addr;

	अगर (addr >= EEPROMVSIZE || (addr & 3))
		वापस -EINVAL;

	pci_ग_लिखो_config_word(hw->pdev, base + PCI_VPD_ADDR, (uपूर्णांक16_t)addr);

	करो अणु
		udelay(10);
		pci_पढ़ो_config_word(hw->pdev, base + PCI_VPD_ADDR, &val);
	पूर्ण जबतक (!(val & PCI_VPD_ADDR_F) && --attempts);

	अगर (!(val & PCI_VPD_ADDR_F)) अणु
		csio_err(hw, "reading EEPROM address 0x%x failed\n", addr);
		वापस -EINVAL;
	पूर्ण

	pci_पढ़ो_config_dword(hw->pdev, base + PCI_VPD_DATA, data);
	*data = le32_to_cpu(*(__le32 *)data);

	वापस 0;
पूर्ण

/*
 * Partial EEPROM Vital Product Data काष्ठाure.  Includes only the ID and
 * VPD-R sections.
 */
काष्ठा t4_vpd_hdr अणु
	u8  id_tag;
	u8  id_len[2];
	u8  id_data[ID_LEN];
	u8  vpdr_tag;
	u8  vpdr_len[2];
पूर्ण;

/*
 *	csio_hw_get_vpd_keyword_val - Locates an inक्रमmation field keyword in
 *				      the VPD
 *	@v: Poपूर्णांकer to buffered vpd data काष्ठाure
 *	@kw: The keyword to search क्रम
 *
 *	Returns the value of the inक्रमmation field keyword or
 *	-EINVAL otherwise.
 */
अटल पूर्णांक
csio_hw_get_vpd_keyword_val(स्थिर काष्ठा t4_vpd_hdr *v, स्थिर अक्षर *kw)
अणु
	पूर्णांक32_t i;
	पूर्णांक32_t offset , len;
	स्थिर uपूर्णांक8_t *buf = &v->id_tag;
	स्थिर uपूर्णांक8_t *vpdr_len = &v->vpdr_tag;
	offset = माप(काष्ठा t4_vpd_hdr);
	len =  (uपूर्णांक16_t)vpdr_len[1] + ((uपूर्णांक16_t)vpdr_len[2] << 8);

	अगर (len + माप(काष्ठा t4_vpd_hdr) > VPD_LEN)
		वापस -EINVAL;

	क्रम (i = offset; (i + VPD_INFO_FLD_HDR_SIZE) <= (offset + len);) अणु
		अगर (स_भेद(buf + i , kw, 2) == 0) अणु
			i += VPD_INFO_FLD_HDR_SIZE;
			वापस i;
		पूर्ण

		i += VPD_INFO_FLD_HDR_SIZE + buf[i+2];
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
csio_pci_capability(काष्ठा pci_dev *pdev, पूर्णांक cap, पूर्णांक *pos)
अणु
	*pos = pci_find_capability(pdev, cap);
	अगर (*pos)
		वापस 0;

	वापस -1;
पूर्ण

/*
 *	csio_hw_get_vpd_params - पढ़ो VPD parameters from VPD EEPROM
 *	@hw: HW module
 *	@p: where to store the parameters
 *
 *	Reads card parameters stored in VPD EEPROM.
 */
अटल पूर्णांक
csio_hw_get_vpd_params(काष्ठा csio_hw *hw, काष्ठा csio_vpd *p)
अणु
	पूर्णांक i, ret, ec, sn, addr;
	uपूर्णांक8_t *vpd, csum;
	स्थिर काष्ठा t4_vpd_hdr *v;
	/* To get around compilation warning from म_मालाip */
	अक्षर __always_unused *s;

	अगर (csio_is_valid_vpd(hw))
		वापस 0;

	ret = csio_pci_capability(hw->pdev, PCI_CAP_ID_VPD,
				  &hw->params.pci.vpd_cap_addr);
	अगर (ret)
		वापस -EINVAL;

	vpd = kzalloc(VPD_LEN, GFP_ATOMIC);
	अगर (vpd == शून्य)
		वापस -ENOMEM;

	/*
	 * Card inक्रमmation normally starts at VPD_BASE but early cards had
	 * it at 0.
	 */
	ret = csio_hw_seeprom_पढ़ो(hw, VPD_BASE, (uपूर्णांक32_t *)(vpd));
	addr = *vpd == 0x82 ? VPD_BASE : VPD_BASE_OLD;

	क्रम (i = 0; i < VPD_LEN; i += 4) अणु
		ret = csio_hw_seeprom_पढ़ो(hw, addr + i, (uपूर्णांक32_t *)(vpd + i));
		अगर (ret) अणु
			kमुक्त(vpd);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Reset the VPD flag! */
	hw->flags &= (~CSIO_HWF_VPD_VALID);

	v = (स्थिर काष्ठा t4_vpd_hdr *)vpd;

#घोषणा FIND_VPD_KW(var, name) करो अणु \
	var = csio_hw_get_vpd_keyword_val(v, name); \
	अगर (var < 0) अणु \
		csio_err(hw, "missing VPD keyword " name "\n"); \
		kमुक्त(vpd); \
		वापस -EINVAL; \
	पूर्ण \
पूर्ण जबतक (0)

	FIND_VPD_KW(i, "RV");
	क्रम (csum = 0; i >= 0; i--)
		csum += vpd[i];

	अगर (csum) अणु
		csio_err(hw, "corrupted VPD EEPROM, actual csum %u\n", csum);
		kमुक्त(vpd);
		वापस -EINVAL;
	पूर्ण
	FIND_VPD_KW(ec, "EC");
	FIND_VPD_KW(sn, "SN");
#अघोषित FIND_VPD_KW

	स_नकल(p->id, v->id_data, ID_LEN);
	s = म_मालाip(p->id);
	स_नकल(p->ec, vpd + ec, EC_LEN);
	s = म_मालाip(p->ec);
	i = vpd[sn - VPD_INFO_FLD_HDR_SIZE + 2];
	स_नकल(p->sn, vpd + sn, min(i, SERNUM_LEN));
	s = म_मालाip(p->sn);

	csio_valid_vpd_copied(hw);

	kमुक्त(vpd);
	वापस 0;
पूर्ण

/*
 *	csio_hw_sf1_पढ़ो - पढ़ो data from the serial flash
 *	@hw: the HW module
 *	@byte_cnt: number of bytes to पढ़ो
 *	@cont: whether another operation will be chained
 *      @lock: whether to lock SF क्रम PL access only
 *	@valp: where to store the पढ़ो data
 *
 *	Reads up to 4 bytes of data from the serial flash.  The location of
 *	the पढ़ो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक
csio_hw_sf1_पढ़ो(काष्ठा csio_hw *hw, uपूर्णांक32_t byte_cnt, पूर्णांक32_t cont,
		 पूर्णांक32_t lock, uपूर्णांक32_t *valp)
अणु
	पूर्णांक ret;

	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (csio_rd_reg32(hw, SF_OP_A) & SF_BUSY_F)
		वापस -EBUSY;

	csio_wr_reg32(hw,  SF_LOCK_V(lock) | SF_CONT_V(cont) |
		      BYTECNT_V(byte_cnt - 1), SF_OP_A);
	ret = csio_hw_रुको_op_करोne_val(hw, SF_OP_A, SF_BUSY_F, 0, SF_ATTEMPTS,
				       10, शून्य);
	अगर (!ret)
		*valp = csio_rd_reg32(hw, SF_DATA_A);
	वापस ret;
पूर्ण

/*
 *	csio_hw_sf1_ग_लिखो - ग_लिखो data to the serial flash
 *	@hw: the HW module
 *	@byte_cnt: number of bytes to ग_लिखो
 *	@cont: whether another operation will be chained
 *      @lock: whether to lock SF क्रम PL access only
 *	@val: value to ग_लिखो
 *
 *	Writes up to 4 bytes of data to the serial flash.  The location of
 *	the ग_लिखो needs to be specअगरied prior to calling this by issuing the
 *	appropriate commands to the serial flash.
 */
अटल पूर्णांक
csio_hw_sf1_ग_लिखो(काष्ठा csio_hw *hw, uपूर्णांक32_t byte_cnt, uपूर्णांक32_t cont,
		  पूर्णांक32_t lock, uपूर्णांक32_t val)
अणु
	अगर (!byte_cnt || byte_cnt > 4)
		वापस -EINVAL;
	अगर (csio_rd_reg32(hw, SF_OP_A) & SF_BUSY_F)
		वापस -EBUSY;

	csio_wr_reg32(hw, val, SF_DATA_A);
	csio_wr_reg32(hw, SF_CONT_V(cont) | BYTECNT_V(byte_cnt - 1) |
		      OP_V(1) | SF_LOCK_V(lock), SF_OP_A);

	वापस csio_hw_रुको_op_करोne_val(hw, SF_OP_A, SF_BUSY_F, 0, SF_ATTEMPTS,
					10, शून्य);
पूर्ण

/*
 *	csio_hw_flash_रुको_op - रुको क्रम a flash operation to complete
 *	@hw: the HW module
 *	@attempts: max number of polls of the status रेजिस्टर
 *	@delay: delay between polls in ms
 *
 *	Wait क्रम a flash operation to complete by polling the status रेजिस्टर.
 */
अटल पूर्णांक
csio_hw_flash_रुको_op(काष्ठा csio_hw *hw, पूर्णांक32_t attempts, पूर्णांक32_t delay)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t status;

	जबतक (1) अणु
		ret = csio_hw_sf1_ग_लिखो(hw, 1, 1, 1, SF_RD_STATUS);
		अगर (ret != 0)
			वापस ret;

		ret = csio_hw_sf1_पढ़ो(hw, 1, 0, 1, &status);
		अगर (ret != 0)
			वापस ret;

		अगर (!(status & 1))
			वापस 0;
		अगर (--attempts == 0)
			वापस -EAGAIN;
		अगर (delay)
			msleep(delay);
	पूर्ण
पूर्ण

/*
 *	csio_hw_पढ़ो_flash - पढ़ो words from serial flash
 *	@hw: the HW module
 *	@addr: the start address क्रम the पढ़ो
 *	@nwords: how many 32-bit words to पढ़ो
 *	@data: where to store the पढ़ो data
 *	@byte_oriented: whether to store data as bytes or as words
 *
 *	Read the specअगरied number of 32-bit words from the serial flash.
 *	If @byte_oriented is set the पढ़ो data is stored as a byte array
 *	(i.e., big-endian), otherwise as 32-bit words in the platक्रमm's
 *	natural endianess.
 */
अटल पूर्णांक
csio_hw_पढ़ो_flash(काष्ठा csio_hw *hw, uपूर्णांक32_t addr, uपूर्णांक32_t nwords,
		  uपूर्णांक32_t *data, पूर्णांक32_t byte_oriented)
अणु
	पूर्णांक ret;

	अगर (addr + nwords * माप(uपूर्णांक32_t) > hw->params.sf_size || (addr & 3))
		वापस -EINVAL;

	addr = swab32(addr) | SF_RD_DATA_FAST;

	ret = csio_hw_sf1_ग_लिखो(hw, 4, 1, 0, addr);
	अगर (ret != 0)
		वापस ret;

	ret = csio_hw_sf1_पढ़ो(hw, 1, 1, 0, data);
	अगर (ret != 0)
		वापस ret;

	क्रम ( ; nwords; nwords--, data++) अणु
		ret = csio_hw_sf1_पढ़ो(hw, 4, nwords > 1, nwords == 1, data);
		अगर (nwords == 1)
			csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */
		अगर (ret)
			वापस ret;
		अगर (byte_oriented)
			*data = (__क्रमce __u32) htonl(*data);
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	csio_hw_ग_लिखो_flash - ग_लिखो up to a page of data to the serial flash
 *	@hw: the hw
 *	@addr: the start address to ग_लिखो
 *	@n: length of data to ग_लिखो in bytes
 *	@data: the data to ग_लिखो
 *
 *	Writes up to a page of data (256 bytes) to the serial flash starting
 *	at the given address.  All the data must be written to the same page.
 */
अटल पूर्णांक
csio_hw_ग_लिखो_flash(काष्ठा csio_hw *hw, uपूर्णांक32_t addr,
		    uपूर्णांक32_t n, स्थिर uपूर्णांक8_t *data)
अणु
	पूर्णांक ret = -EINVAL;
	uपूर्णांक32_t buf[64];
	uपूर्णांक32_t i, c, left, val, offset = addr & 0xff;

	अगर (addr >= hw->params.sf_size || offset + n > SF_PAGE_SIZE)
		वापस -EINVAL;

	val = swab32(addr) | SF_PROG_PAGE;

	ret = csio_hw_sf1_ग_लिखो(hw, 1, 0, 1, SF_WR_ENABLE);
	अगर (ret != 0)
		जाओ unlock;

	ret = csio_hw_sf1_ग_लिखो(hw, 4, 1, 1, val);
	अगर (ret != 0)
		जाओ unlock;

	क्रम (left = n; left; left -= c) अणु
		c = min(left, 4U);
		क्रम (val = 0, i = 0; i < c; ++i)
			val = (val << 8) + *data++;

		ret = csio_hw_sf1_ग_लिखो(hw, c, c != left, 1, val);
		अगर (ret)
			जाओ unlock;
	पूर्ण
	ret = csio_hw_flash_रुको_op(hw, 8, 1);
	अगर (ret)
		जाओ unlock;

	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */

	/* Read the page to verअगरy the ग_लिखो succeeded */
	ret = csio_hw_पढ़ो_flash(hw, addr & ~0xff, ARRAY_SIZE(buf), buf, 1);
	अगर (ret)
		वापस ret;

	अगर (स_भेद(data - n, (uपूर्णांक8_t *)buf + offset, n)) अणु
		csio_err(hw,
			 "failed to correctly write the flash page at %#x\n",
			 addr);
		वापस -EINVAL;
	पूर्ण

	वापस 0;

unlock:
	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */
	वापस ret;
पूर्ण

/*
 *	csio_hw_flash_erase_sectors - erase a range of flash sectors
 *	@hw: the HW module
 *	@start: the first sector to erase
 *	@end: the last sector to erase
 *
 *	Erases the sectors in the given inclusive range.
 */
अटल पूर्णांक
csio_hw_flash_erase_sectors(काष्ठा csio_hw *hw, पूर्णांक32_t start, पूर्णांक32_t end)
अणु
	पूर्णांक ret = 0;

	जबतक (start <= end) अणु

		ret = csio_hw_sf1_ग_लिखो(hw, 1, 0, 1, SF_WR_ENABLE);
		अगर (ret != 0)
			जाओ out;

		ret = csio_hw_sf1_ग_लिखो(hw, 4, 0, 1,
					SF_ERASE_SECTOR | (start << 8));
		अगर (ret != 0)
			जाओ out;

		ret = csio_hw_flash_रुको_op(hw, 14, 500);
		अगर (ret != 0)
			जाओ out;

		start++;
	पूर्ण
out:
	अगर (ret)
		csio_err(hw, "erase of flash sector %d failed, error %d\n",
			 start, ret);
	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */
	वापस 0;
पूर्ण

अटल व्योम
csio_hw_prपूर्णांक_fw_version(काष्ठा csio_hw *hw, अक्षर *str)
अणु
	csio_info(hw, "%s: %u.%u.%u.%u\n", str,
		    FW_HDR_FW_VER_MAJOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MINOR_G(hw->fwrev),
		    FW_HDR_FW_VER_MICRO_G(hw->fwrev),
		    FW_HDR_FW_VER_BUILD_G(hw->fwrev));
पूर्ण

/*
 * csio_hw_get_fw_version - पढ़ो the firmware version
 * @hw: HW module
 * @vers: where to place the version
 *
 * Reads the FW version from flash.
 */
अटल पूर्णांक
csio_hw_get_fw_version(काष्ठा csio_hw *hw, uपूर्णांक32_t *vers)
अणु
	वापस csio_hw_पढ़ो_flash(hw, FLASH_FW_START +
				  दुरत्व(काष्ठा fw_hdr, fw_ver), 1,
				  vers, 0);
पूर्ण

/*
 *	csio_hw_get_tp_version - पढ़ो the TP microcode version
 *	@hw: HW module
 *	@vers: where to place the version
 *
 *	Reads the TP microcode version from flash.
 */
अटल पूर्णांक
csio_hw_get_tp_version(काष्ठा csio_hw *hw, u32 *vers)
अणु
	वापस csio_hw_पढ़ो_flash(hw, FLASH_FW_START +
			दुरत्व(काष्ठा fw_hdr, tp_microcode_ver), 1,
			vers, 0);
पूर्ण

/*
 * csio_hw_fw_dload - करोwnload firmware.
 * @hw: HW module
 * @fw_data: firmware image to ग_लिखो.
 * @size: image size
 *
 * Write the supplied firmware image to the card's serial flash.
 */
अटल पूर्णांक
csio_hw_fw_dload(काष्ठा csio_hw *hw, uपूर्णांक8_t *fw_data, uपूर्णांक32_t size)
अणु
	uपूर्णांक32_t csum;
	पूर्णांक32_t addr;
	पूर्णांक ret;
	uपूर्णांक32_t i;
	uपूर्णांक8_t first_page[SF_PAGE_SIZE];
	स्थिर __be32 *p = (स्थिर __be32 *)fw_data;
	काष्ठा fw_hdr *hdr = (काष्ठा fw_hdr *)fw_data;
	uपूर्णांक32_t sf_sec_size;

	अगर ((!hw->params.sf_size) || (!hw->params.sf_nsec)) अणु
		csio_err(hw, "Serial Flash data invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!size) अणु
		csio_err(hw, "FW image has no data\n");
		वापस -EINVAL;
	पूर्ण

	अगर (size & 511) अणु
		csio_err(hw, "FW image size not multiple of 512 bytes\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ntohs(hdr->len512) * 512 != size) अणु
		csio_err(hw, "FW image size differs from size in FW header\n");
		वापस -EINVAL;
	पूर्ण

	अगर (size > FLASH_FW_MAX_SIZE) अणु
		csio_err(hw, "FW image too large, max is %u bytes\n",
			    FLASH_FW_MAX_SIZE);
		वापस -EINVAL;
	पूर्ण

	क्रम (csum = 0, i = 0; i < size / माप(csum); i++)
		csum += ntohl(p[i]);

	अगर (csum != 0xffffffff) अणु
		csio_err(hw, "corrupted firmware image, checksum %#x\n", csum);
		वापस -EINVAL;
	पूर्ण

	sf_sec_size = hw->params.sf_size / hw->params.sf_nsec;
	i = DIV_ROUND_UP(size, sf_sec_size);        /* # of sectors spanned */

	csio_dbg(hw, "Erasing sectors... start:%d end:%d\n",
			  FLASH_FW_START_SEC, FLASH_FW_START_SEC + i - 1);

	ret = csio_hw_flash_erase_sectors(hw, FLASH_FW_START_SEC,
					  FLASH_FW_START_SEC + i - 1);
	अगर (ret) अणु
		csio_err(hw, "Flash Erase failed\n");
		जाओ out;
	पूर्ण

	/*
	 * We ग_लिखो the correct version at the end so the driver can see a bad
	 * version अगर the FW ग_लिखो fails.  Start by writing a copy of the
	 * first page with a bad version.
	 */
	स_नकल(first_page, fw_data, SF_PAGE_SIZE);
	((काष्ठा fw_hdr *)first_page)->fw_ver = htonl(0xffffffff);
	ret = csio_hw_ग_लिखो_flash(hw, FLASH_FW_START, SF_PAGE_SIZE, first_page);
	अगर (ret)
		जाओ out;

	csio_dbg(hw, "Writing Flash .. start:%d end:%d\n",
		    FW_IMG_START, FW_IMG_START + size);

	addr = FLASH_FW_START;
	क्रम (size -= SF_PAGE_SIZE; size; size -= SF_PAGE_SIZE) अणु
		addr += SF_PAGE_SIZE;
		fw_data += SF_PAGE_SIZE;
		ret = csio_hw_ग_लिखो_flash(hw, addr, SF_PAGE_SIZE, fw_data);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = csio_hw_ग_लिखो_flash(hw,
				  FLASH_FW_START +
					दुरत्व(काष्ठा fw_hdr, fw_ver),
				  माप(hdr->fw_ver),
				  (स्थिर uपूर्णांक8_t *)&hdr->fw_ver);

out:
	अगर (ret)
		csio_err(hw, "firmware download failed, error %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक
csio_hw_get_flash_params(काष्ठा csio_hw *hw)
अणु
	/* Table क्रम non-Numonix supported flash parts.  Numonix parts are left
	 * to the preexisting code.  All flash parts have 64KB sectors.
	 */
	अटल काष्ठा flash_desc अणु
		u32 venकरोr_and_model_id;
		u32 size_mb;
	पूर्ण supported_flash[] = अणु
		अणु 0x150201, 4 << 20 पूर्ण,       /* Spansion 4MB S25FL032P */
	पूर्ण;

	u32 part, manufacturer;
	u32 density, size = 0;
	u32 flashid = 0;
	पूर्णांक ret;

	ret = csio_hw_sf1_ग_लिखो(hw, 1, 1, 0, SF_RD_ID);
	अगर (!ret)
		ret = csio_hw_sf1_पढ़ो(hw, 3, 0, 1, &flashid);
	csio_wr_reg32(hw, 0, SF_OP_A);    /* unlock SF */
	अगर (ret)
		वापस ret;

	/* Check to see अगर it's one of our non-standard supported Flash parts.
	 */
	क्रम (part = 0; part < ARRAY_SIZE(supported_flash); part++)
		अगर (supported_flash[part].venकरोr_and_model_id == flashid) अणु
			hw->params.sf_size = supported_flash[part].size_mb;
			hw->params.sf_nsec =
				hw->params.sf_size / SF_SEC_SIZE;
			जाओ found;
		पूर्ण

	/* Decode Flash part size.  The code below looks repetitive with
	 * common encodings, but that's not guaranteed in the JEDEC
	 * specअगरication क्रम the Read JEDEC ID command.  The only thing that
	 * we're guaranteed by the JEDEC specअगरication is where the
	 * Manufacturer ID is in the वापसed result.  After that each
	 * Manufacturer ~could~ encode things completely dअगरferently.
	 * Note, all Flash parts must have 64KB sectors.
	 */
	manufacturer = flashid & 0xff;
	चयन (manufacturer) अणु
	हाल 0x20: अणु /* Micron/Numonix */
		/* This Density -> Size decoding table is taken from Micron
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x14 ... 0x19: /* 1MB - 32MB */
			size = 1 << density;
			अवरोध;
		हाल 0x20: /* 64MB */
			size = 1 << 26;
			अवरोध;
		हाल 0x21: /* 128MB */
			size = 1 << 27;
			अवरोध;
		हाल 0x22: /* 256MB */
			size = 1 << 28;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 0x9d: अणु /* ISSI -- Integrated Silicon Solution, Inc. */
		/* This Density -> Size decoding table is taken from ISSI
		 * Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x16: /* 32 MB */
			size = 1 << 25;
			अवरोध;
		हाल 0x17: /* 64MB */
			size = 1 << 26;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 0xc2: /* Macronix */
	हाल 0xef: /* Winbond */ अणु
		/* This Density -> Size decoding table is taken from
		 * Macronix and Winbond Data Sheets.
		 */
		density = (flashid >> 16) & 0xff;
		चयन (density) अणु
		हाल 0x17: /* 8MB */
		हाल 0x18: /* 16MB */
			size = 1 << density;
		पूर्ण
	पूर्ण
	पूर्ण

	/* If we didn't recognize the FLASH part, that's no real issue: the
	 * Hardware/Software contract says that Hardware will _*ALWAYS*_
	 * use a FLASH part which is at least 4MB in size and has 64KB
	 * sectors.  The unrecognized FLASH part is likely to be much larger
	 * than 4MB, but that's all we really need.
	 */
	अगर (size == 0) अणु
		csio_warn(hw, "Unknown Flash Part, ID = %#x, assuming 4MB\n",
			  flashid);
		size = 1 << 22;
	पूर्ण

	/* Store decoded Flash size */
	hw->params.sf_size = size;
	hw->params.sf_nsec = size / SF_SEC_SIZE;

found:
	अगर (hw->params.sf_size < FLASH_MIN_SIZE)
		csio_warn(hw, "WARNING: Flash Part ID %#x, size %#x < %#x\n",
			  flashid, hw->params.sf_size, FLASH_MIN_SIZE);
	वापस 0;
पूर्ण

/*****************************************************************************/
/* HW State machine assists                                                  */
/*****************************************************************************/

अटल पूर्णांक
csio_hw_dev_पढ़ोy(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक32_t reg;
	पूर्णांक cnt = 6;
	पूर्णांक src_pf;

	जबतक (((reg = csio_rd_reg32(hw, PL_WHOAMI_A)) == 0xFFFFFFFF) &&
	       (--cnt != 0))
		mdelay(100);

	अगर (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		src_pf = SOURCEPF_G(reg);
	अन्यथा
		src_pf = T6_SOURCEPF_G(reg);

	अगर ((cnt == 0) && (((पूर्णांक32_t)(src_pf) < 0) ||
			   (src_pf >= CSIO_MAX_PFN))) अणु
		csio_err(hw, "PL_WHOAMI returned 0x%x, cnt:%d\n", reg, cnt);
		वापस -EIO;
	पूर्ण

	hw->pfn = src_pf;

	वापस 0;
पूर्ण

/*
 * csio_करो_hello - Perक्रमm the HELLO FW Mailbox command and process response.
 * @hw: HW module
 * @state: Device state
 *
 * FW_HELLO_CMD has to be polled क्रम completion.
 */
अटल पूर्णांक
csio_करो_hello(काष्ठा csio_hw *hw, क्रमागत csio_dev_state *state)
अणु
	काष्ठा csio_mb	*mbp;
	पूर्णांक	rv = 0;
	क्रमागत fw_retval retval;
	uपूर्णांक8_t mpfn;
	अक्षर state_str[16];
	पूर्णांक retries = FW_CMD_HELLO_RETRIES;

	स_रखो(state_str, 0, माप(state_str));

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		rv = -ENOMEM;
		CSIO_INC_STATS(hw, n_err_nomem);
		जाओ out;
	पूर्ण

retry:
	csio_mb_hello(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn,
		      hw->pfn, CSIO_MASTER_MAY, शून्य);

	rv = csio_mb_issue(hw, mbp);
	अगर (rv) अणु
		csio_err(hw, "failed to issue HELLO cmd. ret:%d.\n", rv);
		जाओ out_मुक्त_mb;
	पूर्ण

	csio_mb_process_hello_rsp(hw, mbp, &retval, state, &mpfn);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "HELLO cmd failed with ret: %d\n", retval);
		rv = -EINVAL;
		जाओ out_मुक्त_mb;
	पूर्ण

	/* Firmware has designated us to be master */
	अगर (hw->pfn == mpfn) अणु
		hw->flags |= CSIO_HWF_MASTER;
	पूर्ण अन्यथा अगर (*state == CSIO_DEV_STATE_UNINIT) अणु
		/*
		 * If we're not the Master PF then we need to रुको around क्रम
		 * the Master PF Driver to finish setting up the adapter.
		 *
		 * Note that we also करो this रुको अगर we're a non-Master-capable
		 * PF and there is no current Master PF; a Master PF may show up
		 * momentarily and we wouldn't want to fail poपूर्णांकlessly.  (This
		 * can happen when an OS loads lots of dअगरferent drivers rapidly
		 * at the same समय). In this हाल, the Master PF वापसed by
		 * the firmware will be PCIE_FW_MASTER_MASK so the test below
		 * will work ...
		 */

		पूर्णांक रुकोing = FW_CMD_HELLO_TIMEOUT;

		/*
		 * Wait क्रम the firmware to either indicate an error or
		 * initialized state.  If we see either of these we bail out
		 * and report the issue to the caller.  If we exhaust the
		 * "hello timeout" and we haven't exhausted our retries, try
		 * again.  Otherwise bail with a समयout error.
		 */
		क्रम (;;) अणु
			uपूर्णांक32_t pcie_fw;

			spin_unlock_irq(&hw->lock);
			msleep(50);
			spin_lock_irq(&hw->lock);
			रुकोing -= 50;

			/*
			 * If neither Error nor Initialized are indicated
			 * by the firmware keep रुकोing till we exhaust our
			 * समयout ... and then retry अगर we haven't exhausted
			 * our retries ...
			 */
			pcie_fw = csio_rd_reg32(hw, PCIE_FW_A);
			अगर (!(pcie_fw & (PCIE_FW_ERR_F|PCIE_FW_INIT_F))) अणु
				अगर (रुकोing <= 0) अणु
					अगर (retries-- > 0)
						जाओ retry;

					rv = -ETIMEDOUT;
					अवरोध;
				पूर्ण
				जारी;
			पूर्ण

			/*
			 * We either have an Error or Initialized condition
			 * report errors preferentially.
			 */
			अगर (state) अणु
				अगर (pcie_fw & PCIE_FW_ERR_F) अणु
					*state = CSIO_DEV_STATE_ERR;
					rv = -ETIMEDOUT;
				पूर्ण अन्यथा अगर (pcie_fw & PCIE_FW_INIT_F)
					*state = CSIO_DEV_STATE_INIT;
			पूर्ण

			/*
			 * If we arrived beक्रमe a Master PF was selected and
			 * there's not a valid Master PF, grab its identity
			 * क्रम our caller.
			 */
			अगर (mpfn == PCIE_FW_MASTER_M &&
			    (pcie_fw & PCIE_FW_MASTER_VLD_F))
				mpfn = PCIE_FW_MASTER_G(pcie_fw);
			अवरोध;
		पूर्ण
		hw->flags &= ~CSIO_HWF_MASTER;
	पूर्ण

	चयन (*state) अणु
	हाल CSIO_DEV_STATE_UNINIT:
		म_नकल(state_str, "Initializing");
		अवरोध;
	हाल CSIO_DEV_STATE_INIT:
		म_नकल(state_str, "Initialized");
		अवरोध;
	हाल CSIO_DEV_STATE_ERR:
		म_नकल(state_str, "Error");
		अवरोध;
	शेष:
		म_नकल(state_str, "Unknown");
		अवरोध;
	पूर्ण

	अगर (hw->pfn == mpfn)
		csio_info(hw, "PF: %d, Coming up as MASTER, HW state: %s\n",
			hw->pfn, state_str);
	अन्यथा
		csio_info(hw,
		    "PF: %d, Coming up as SLAVE, Master PF: %d, HW state: %s\n",
		    hw->pfn, mpfn, state_str);

out_मुक्त_mb:
	mempool_मुक्त(mbp, hw->mb_mempool);
out:
	वापस rv;
पूर्ण

/*
 * csio_करो_bye - Perक्रमm the BYE FW Mailbox command and process response.
 * @hw: HW module
 *
 */
अटल पूर्णांक
csio_करो_bye(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	csio_mb_bye(hw, mbp, CSIO_MB_DEFAULT_TMO, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of BYE command failed\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	retval = csio_mb_fw_retval(mbp);
	अगर (retval != FW_SUCCESS) अणु
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

/*
 * csio_करो_reset- Perक्रमm the device reset.
 * @hw: HW module
 * @fw_rst: FW reset
 *
 * If fw_rst is set, issues FW reset mbox cmd otherwise
 * करोes PIO reset.
 * Perक्रमms reset of the function.
 */
अटल पूर्णांक
csio_करो_reset(काष्ठा csio_hw *hw, bool fw_rst)
अणु
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;

	अगर (!fw_rst) अणु
		/* PIO reset */
		csio_wr_reg32(hw, PIORSTMODE_F | PIORST_F, PL_RST_A);
		mdelay(2000);
		वापस 0;
	पूर्ण

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	csio_mb_reset(hw, mbp, CSIO_MB_DEFAULT_TMO,
		      PIORSTMODE_F | PIORST_F, 0, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of RESET command failed.n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	retval = csio_mb_fw_retval(mbp);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "RESET cmd failed with ret:0x%x.\n", retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

अटल पूर्णांक
csio_hw_validate_caps(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp)
अणु
	काष्ठा fw_caps_config_cmd *rsp = (काष्ठा fw_caps_config_cmd *)mbp->mb;
	uपूर्णांक16_t caps;

	caps = ntohs(rsp->fcoecaps);

	अगर (!(caps & FW_CAPS_CONFIG_FCOE_INITIATOR)) अणु
		csio_err(hw, "No FCoE Initiator capability in the firmware.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(caps & FW_CAPS_CONFIG_FCOE_CTRL_OFLD)) अणु
		csio_err(hw, "No FCoE Control Offload capability\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	csio_hw_fw_halt - issue a reset/halt to FW and put uP पूर्णांकo RESET
 *	@hw: the HW module
 *	@mbox: mailbox to use क्रम the FW RESET command (अगर desired)
 *	@क्रमce: क्रमce uP पूर्णांकo RESET even अगर FW RESET command fails
 *
 *	Issues a RESET command to firmware (अगर desired) with a HALT indication
 *	and then माला_दो the microprocessor पूर्णांकo RESET state.  The RESET command
 *	will only be issued अगर a legitimate mailbox is provided (mbox <=
 *	PCIE_FW_MASTER_MASK).
 *
 *	This is generally used in order क्रम the host to safely manipulate the
 *	adapter without fear of conflicting with whatever the firmware might
 *	be करोing.  The only way out of this state is to RESTART the firmware
 *	...
 */
अटल पूर्णांक
csio_hw_fw_halt(काष्ठा csio_hw *hw, uपूर्णांक32_t mbox, पूर्णांक32_t क्रमce)
अणु
	क्रमागत fw_retval retval = 0;

	/*
	 * If a legitimate mailbox is provided, issue a RESET command
	 * with a HALT indication.
	 */
	अगर (mbox <= PCIE_FW_MASTER_M) अणु
		काष्ठा csio_mb	*mbp;

		mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
		अगर (!mbp) अणु
			CSIO_INC_STATS(hw, n_err_nomem);
			वापस -ENOMEM;
		पूर्ण

		csio_mb_reset(hw, mbp, CSIO_MB_DEFAULT_TMO,
			      PIORSTMODE_F | PIORST_F, FW_RESET_CMD_HALT_F,
			      शून्य);

		अगर (csio_mb_issue(hw, mbp)) अणु
			csio_err(hw, "Issue of RESET command failed!\n");
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण

		retval = csio_mb_fw_retval(mbp);
		mempool_मुक्त(mbp, hw->mb_mempool);
	पूर्ण

	/*
	 * Normally we won't complete the operation अगर the firmware RESET
	 * command fails but अगर our caller insists we'll go ahead and put the
	 * uP पूर्णांकo RESET.  This can be useful अगर the firmware is hung or even
	 * missing ...  We'll have to take the risk of putting the uP पूर्णांकo
	 * RESET without the cooperation of firmware in that हाल.
	 *
	 * We also क्रमce the firmware's HALT flag to be on in हाल we bypassed
	 * the firmware RESET command above or we're dealing with old firmware
	 * which करोesn't have the HALT capability.  This will serve as a flag
	 * क्रम the incoming firmware to know that it's coming out of a HALT
	 * rather than a RESET ... अगर it's new enough to understand that ...
	 */
	अगर (retval == 0 || क्रमce) अणु
		csio_set_reg_field(hw, CIM_BOOT_CFG_A, UPCRST_F, UPCRST_F);
		csio_set_reg_field(hw, PCIE_FW_A, PCIE_FW_HALT_F,
				   PCIE_FW_HALT_F);
	पूर्ण

	/*
	 * And we always वापस the result of the firmware RESET command
	 * even when we क्रमce the uP पूर्णांकo RESET ...
	 */
	वापस retval ? -EINVAL : 0;
पूर्ण

/*
 *	csio_hw_fw_restart - restart the firmware by taking the uP out of RESET
 *	@hw: the HW module
 *	@reset: अगर we want to करो a RESET to restart things
 *
 *	Restart firmware previously halted by csio_hw_fw_halt().  On successful
 *	वापस the previous PF Master reमुख्यs as the new PF Master and there
 *	is no need to issue a new HELLO command, etc.
 *
 *	We करो this in two ways:
 *
 *	 1. If we're dealing with newer firmware we'll simply want to take
 *	    the chip's microprocessor out of RESET.  This will cause the
 *	    firmware to start up from its start vector.  And then we'll loop
 *	    until the firmware indicates it's started again (PCIE_FW.HALT
 *	    reset to 0) or we समयout.
 *
 *	 2. If we're dealing with older firmware then we'll need to RESET
 *	    the chip since older firmware won't recognize the PCIE_FW.HALT
 *	    flag and स्वतःmatically RESET itself on startup.
 */
अटल पूर्णांक
csio_hw_fw_restart(काष्ठा csio_hw *hw, uपूर्णांक32_t mbox, पूर्णांक32_t reset)
अणु
	अगर (reset) अणु
		/*
		 * Since we're directing the RESET instead of the firmware
		 * करोing it स्वतःmatically, we need to clear the PCIE_FW.HALT
		 * bit.
		 */
		csio_set_reg_field(hw, PCIE_FW_A, PCIE_FW_HALT_F, 0);

		/*
		 * If we've been given a valid mailbox, first try to get the
		 * firmware to करो the RESET.  If that works, great and we can
		 * वापस success.  Otherwise, अगर we haven't been given a
		 * valid mailbox or the RESET command failed, fall back to
		 * hitting the chip with a hammer.
		 */
		अगर (mbox <= PCIE_FW_MASTER_M) अणु
			csio_set_reg_field(hw, CIM_BOOT_CFG_A, UPCRST_F, 0);
			msleep(100);
			अगर (csio_करो_reset(hw, true) == 0)
				वापस 0;
		पूर्ण

		csio_wr_reg32(hw, PIORSTMODE_F | PIORST_F, PL_RST_A);
		msleep(2000);
	पूर्ण अन्यथा अणु
		पूर्णांक ms;

		csio_set_reg_field(hw, CIM_BOOT_CFG_A, UPCRST_F, 0);
		क्रम (ms = 0; ms < FW_CMD_MAX_TIMEOUT; ) अणु
			अगर (!(csio_rd_reg32(hw, PCIE_FW_A) & PCIE_FW_HALT_F))
				वापस 0;
			msleep(100);
			ms += 100;
		पूर्ण
		वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *	csio_hw_fw_upgrade - perक्रमm all of the steps necessary to upgrade FW
 *	@hw: the HW module
 *	@mbox: mailbox to use क्रम the FW RESET command (अगर desired)
 *	@fw_data: the firmware image to ग_लिखो
 *	@size: image size
 *	@क्रमce: क्रमce upgrade even अगर firmware करोesn't cooperate
 *
 *	Perक्रमm all of the steps necessary क्रम upgrading an adapter's
 *	firmware image.  Normally this requires the cooperation of the
 *	existing firmware in order to halt all existing activities
 *	but अगर an invalid mailbox token is passed in we skip that step
 *	(though we'll still put the adapter microprocessor पूर्णांकo RESET in
 *	that हाल).
 *
 *	On successful वापस the new firmware will have been loaded and
 *	the adapter will have been fully RESET losing all previous setup
 *	state.  On unsuccessful वापस the adapter may be completely hosed ...
 *	positive त्रुटि_सं indicates that the adapter is ~probably~ पूर्णांकact, a
 *	negative त्रुटि_सं indicates that things are looking bad ...
 */
अटल पूर्णांक
csio_hw_fw_upgrade(काष्ठा csio_hw *hw, uपूर्णांक32_t mbox,
		  स्थिर u8 *fw_data, uपूर्णांक32_t size, पूर्णांक32_t क्रमce)
अणु
	स्थिर काष्ठा fw_hdr *fw_hdr = (स्थिर काष्ठा fw_hdr *)fw_data;
	पूर्णांक reset, ret;

	ret = csio_hw_fw_halt(hw, mbox, क्रमce);
	अगर (ret != 0 && !क्रमce)
		वापस ret;

	ret = csio_hw_fw_dload(hw, (uपूर्णांक8_t *) fw_data, size);
	अगर (ret != 0)
		वापस ret;

	/*
	 * Older versions of the firmware करोn't understand the new
	 * PCIE_FW.HALT flag and so won't know to perक्रमm a RESET when they
	 * restart.  So क्रम newly loaded older firmware we'll have to करो the
	 * RESET क्रम it so it starts up on a clean slate.  We can tell अगर
	 * the newly loaded firmware will handle this right by checking
	 * its header flags to see अगर it advertises the capability.
	 */
	reset = ((ntohl(fw_hdr->flags) & FW_HDR_FLAGS_RESET_HALT) == 0);
	वापस csio_hw_fw_restart(hw, mbox, reset);
पूर्ण

/*
 * csio_get_device_params - Get device parameters.
 * @hw: HW module
 *
 */
अटल पूर्णांक
csio_get_device_params(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_wrm *wrm	= csio_hw_to_wrm(hw);
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;
	u32 param[6];
	पूर्णांक i, j = 0;

	/* Initialize portids to -1 */
	क्रम (i = 0; i < CSIO_MAX_PPORTS; i++)
		hw->pport[i].portid = -1;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Get port vec inक्रमmation. */
	param[0] = FW_PARAM_DEV(PORTVEC);

	/* Get Core घड़ी. */
	param[1] = FW_PARAM_DEV(CCLK);

	/* Get EQ id start and end. */
	param[2] = FW_PARAM_PFVF(EQ_START);
	param[3] = FW_PARAM_PFVF(EQ_END);

	/* Get IQ id start and end. */
	param[4] = FW_PARAM_PFVF(IQFLINT_START);
	param[5] = FW_PARAM_PFVF(IQFLINT_END);

	csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn, 0,
		       ARRAY_SIZE(param), param, शून्य, false, शून्य);
	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of FW_PARAMS_CMD(read) failed!\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	csio_mb_process_पढ़ो_params_rsp(hw, mbp, &retval,
			ARRAY_SIZE(param), param);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FW_PARAMS_CMD(read) failed with ret:0x%x!\n",
				retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	/* cache the inक्रमmation. */
	hw->port_vec = param[0];
	hw->vpd.cclk = param[1];
	wrm->fw_eq_start = param[2];
	wrm->fw_iq_start = param[4];

	/* Using FW configured max iqs & eqs */
	अगर ((hw->flags & CSIO_HWF_USING_SOFT_PARAMS) ||
		!csio_is_hw_master(hw)) अणु
		hw->cfg_niq = param[5] - param[4] + 1;
		hw->cfg_neq = param[3] - param[2] + 1;
		csio_dbg(hw, "Using fwconfig max niqs %d neqs %d\n",
			hw->cfg_niq, hw->cfg_neq);
	पूर्ण

	hw->port_vec &= csio_port_mask;

	hw->num_pports	= hweight32(hw->port_vec);

	csio_dbg(hw, "Port vector: 0x%x, #ports: %d\n",
		    hw->port_vec, hw->num_pports);

	क्रम (i = 0; i < hw->num_pports; i++) अणु
		जबतक ((hw->port_vec & (1 << j)) == 0)
			j++;
		hw->pport[i].portid = j++;
		csio_dbg(hw, "Found Port:%d\n", hw->pport[i].portid);
	पूर्ण
	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण


/*
 * csio_config_device_caps - Get and set device capabilities.
 * @hw: HW module
 *
 */
अटल पूर्णांक
csio_config_device_caps(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;
	पूर्णांक rv = -EINVAL;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Get device capabilities */
	csio_mb_caps_config(hw, mbp, CSIO_MB_DEFAULT_TMO, 0, 0, 0, 0, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of FW_CAPS_CONFIG_CMD(r) failed!\n");
		जाओ out;
	पूर्ण

	retval = csio_mb_fw_retval(mbp);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FW_CAPS_CONFIG_CMD(r) returned %d!\n", retval);
		जाओ out;
	पूर्ण

	/* Validate device capabilities */
	rv = csio_hw_validate_caps(hw, mbp);
	अगर (rv != 0)
		जाओ out;

	/* Don't config device capabilities अगर alपढ़ोy configured */
	अगर (hw->fw_state == CSIO_DEV_STATE_INIT) अणु
		rv = 0;
		जाओ out;
	पूर्ण

	/* Write back desired device capabilities */
	csio_mb_caps_config(hw, mbp, CSIO_MB_DEFAULT_TMO, true, true,
			    false, true, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of FW_CAPS_CONFIG_CMD(w) failed!\n");
		जाओ out;
	पूर्ण

	retval = csio_mb_fw_retval(mbp);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FW_CAPS_CONFIG_CMD(w) returned %d!\n", retval);
		जाओ out;
	पूर्ण

	rv = 0;
out:
	mempool_मुक्त(mbp, hw->mb_mempool);
	वापस rv;
पूर्ण

अटल अंतरभूत क्रमागत cc_fec fwcap_to_cc_fec(fw_port_cap32_t fw_fec)
अणु
	क्रमागत cc_fec cc_fec = 0;

	अगर (fw_fec & FW_PORT_CAP32_FEC_RS)
		cc_fec |= FEC_RS;
	अगर (fw_fec & FW_PORT_CAP32_FEC_BASER_RS)
		cc_fec |= FEC_BASER_RS;

	वापस cc_fec;
पूर्ण

अटल अंतरभूत fw_port_cap32_t cc_to_fwcap_छोड़ो(क्रमागत cc_छोड़ो cc_छोड़ो)
अणु
	fw_port_cap32_t fw_छोड़ो = 0;

	अगर (cc_छोड़ो & PAUSE_RX)
		fw_छोड़ो |= FW_PORT_CAP32_FC_RX;
	अगर (cc_छोड़ो & PAUSE_TX)
		fw_छोड़ो |= FW_PORT_CAP32_FC_TX;

	वापस fw_छोड़ो;
पूर्ण

अटल अंतरभूत fw_port_cap32_t cc_to_fwcap_fec(क्रमागत cc_fec cc_fec)
अणु
	fw_port_cap32_t fw_fec = 0;

	अगर (cc_fec & FEC_RS)
		fw_fec |= FW_PORT_CAP32_FEC_RS;
	अगर (cc_fec & FEC_BASER_RS)
		fw_fec |= FW_PORT_CAP32_FEC_BASER_RS;

	वापस fw_fec;
पूर्ण

/**
 * fwcap_to_fwspeed - वापस highest speed in Port Capabilities
 * @acaps: advertised Port Capabilities
 *
 * Get the highest speed क्रम the port from the advertised Port
 * Capabilities.
 */
fw_port_cap32_t fwcap_to_fwspeed(fw_port_cap32_t acaps)
अणु
	#घोषणा TEST_SPEED_RETURN(__caps_speed) \
		करो अणु \
			अगर (acaps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				वापस FW_PORT_CAP32_SPEED_##__caps_speed; \
		पूर्ण जबतक (0)

	TEST_SPEED_RETURN(400G);
	TEST_SPEED_RETURN(200G);
	TEST_SPEED_RETURN(100G);
	TEST_SPEED_RETURN(50G);
	TEST_SPEED_RETURN(40G);
	TEST_SPEED_RETURN(25G);
	TEST_SPEED_RETURN(10G);
	TEST_SPEED_RETURN(1G);
	TEST_SPEED_RETURN(100M);

	#अघोषित TEST_SPEED_RETURN

	वापस 0;
पूर्ण

/**
 *      fwcaps16_to_caps32 - convert 16-bit Port Capabilities to 32-bits
 *      @caps16: a 16-bit Port Capabilities value
 *
 *      Returns the equivalent 32-bit Port Capabilities value.
 */
fw_port_cap32_t fwcaps16_to_caps32(fw_port_cap16_t caps16)
अणु
	fw_port_cap32_t caps32 = 0;

	#घोषणा CAP16_TO_CAP32(__cap) \
		करो अणु \
			अगर (caps16 & FW_PORT_CAP_##__cap) \
				caps32 |= FW_PORT_CAP32_##__cap; \
		पूर्ण जबतक (0)

	CAP16_TO_CAP32(SPEED_100M);
	CAP16_TO_CAP32(SPEED_1G);
	CAP16_TO_CAP32(SPEED_25G);
	CAP16_TO_CAP32(SPEED_10G);
	CAP16_TO_CAP32(SPEED_40G);
	CAP16_TO_CAP32(SPEED_100G);
	CAP16_TO_CAP32(FC_RX);
	CAP16_TO_CAP32(FC_TX);
	CAP16_TO_CAP32(ANEG);
	CAP16_TO_CAP32(MDIAUTO);
	CAP16_TO_CAP32(MDISTRAIGHT);
	CAP16_TO_CAP32(FEC_RS);
	CAP16_TO_CAP32(FEC_BASER_RS);
	CAP16_TO_CAP32(802_3_PAUSE);
	CAP16_TO_CAP32(802_3_ASM_सूची);

	#अघोषित CAP16_TO_CAP32

	वापस caps32;
पूर्ण

/**
 *	fwcaps32_to_caps16 - convert 32-bit Port Capabilities to 16-bits
 *	@caps32: a 32-bit Port Capabilities value
 *
 *	Returns the equivalent 16-bit Port Capabilities value.  Note that
 *	not all 32-bit Port Capabilities can be represented in the 16-bit
 *	Port Capabilities and some fields/values may not make it.
 */
fw_port_cap16_t fwcaps32_to_caps16(fw_port_cap32_t caps32)
अणु
	fw_port_cap16_t caps16 = 0;

	#घोषणा CAP32_TO_CAP16(__cap) \
		करो अणु \
			अगर (caps32 & FW_PORT_CAP32_##__cap) \
				caps16 |= FW_PORT_CAP_##__cap; \
		पूर्ण जबतक (0)

	CAP32_TO_CAP16(SPEED_100M);
	CAP32_TO_CAP16(SPEED_1G);
	CAP32_TO_CAP16(SPEED_10G);
	CAP32_TO_CAP16(SPEED_25G);
	CAP32_TO_CAP16(SPEED_40G);
	CAP32_TO_CAP16(SPEED_100G);
	CAP32_TO_CAP16(FC_RX);
	CAP32_TO_CAP16(FC_TX);
	CAP32_TO_CAP16(802_3_PAUSE);
	CAP32_TO_CAP16(802_3_ASM_सूची);
	CAP32_TO_CAP16(ANEG);
	CAP32_TO_CAP16(FORCE_PAUSE);
	CAP32_TO_CAP16(MDIAUTO);
	CAP32_TO_CAP16(MDISTRAIGHT);
	CAP32_TO_CAP16(FEC_RS);
	CAP32_TO_CAP16(FEC_BASER_RS);

	#अघोषित CAP32_TO_CAP16

	वापस caps16;
पूर्ण

/**
 *      lstatus_to_fwcap - translate old lstatus to 32-bit Port Capabilities
 *      @lstatus: old FW_PORT_ACTION_GET_PORT_INFO lstatus value
 *
 *      Translates old FW_PORT_ACTION_GET_PORT_INFO lstatus field पूर्णांकo new
 *      32-bit Port Capabilities value.
 */
fw_port_cap32_t lstatus_to_fwcap(u32 lstatus)
अणु
	fw_port_cap32_t linkattr = 0;

	/* The क्रमmat of the Link Status in the old
	 * 16-bit Port Inक्रमmation message isn't the same as the
	 * 16-bit Port Capabilities bitfield used everywhere अन्यथा.
	 */
	अगर (lstatus & FW_PORT_CMD_RXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_RX;
	अगर (lstatus & FW_PORT_CMD_TXPAUSE_F)
		linkattr |= FW_PORT_CAP32_FC_TX;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100M))
		linkattr |= FW_PORT_CAP32_SPEED_100M;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_1G))
		linkattr |= FW_PORT_CAP32_SPEED_1G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_10G))
		linkattr |= FW_PORT_CAP32_SPEED_10G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_25G))
		linkattr |= FW_PORT_CAP32_SPEED_25G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_40G))
		linkattr |= FW_PORT_CAP32_SPEED_40G;
	अगर (lstatus & FW_PORT_CMD_LSPEED_V(FW_PORT_CAP_SPEED_100G))
		linkattr |= FW_PORT_CAP32_SPEED_100G;

	वापस linkattr;
पूर्ण

/**
 *      csio_init_link_config - initialize a link's SW state
 *      @lc: poपूर्णांकer to काष्ठाure holding the link state
 *      @pcaps: link Port Capabilities
 *      @acaps: link current Advertised Port Capabilities
 *
 *      Initializes the SW state मुख्यtained क्रम each link, including the link's
 *      capabilities and शेष speed/flow-control/स्वतःnegotiation settings.
 */
अटल व्योम csio_init_link_config(काष्ठा link_config *lc, fw_port_cap32_t pcaps,
				  fw_port_cap32_t acaps)
अणु
	lc->pcaps = pcaps;
	lc->def_acaps = acaps;
	lc->lpacaps = 0;
	lc->speed_caps = 0;
	lc->speed = 0;
	lc->requested_fc = PAUSE_RX | PAUSE_TX;
	lc->fc = lc->requested_fc;

	/*
	 * For Forward Error Control, we शेष to whatever the Firmware
	 * tells us the Link is currently advertising.
	 */
	lc->requested_fec = FEC_AUTO;
	lc->fec = fwcap_to_cc_fec(lc->def_acaps);

	/* If the Port is capable of Auto-Negtotiation, initialize it as
	 * "enabled" and copy over all of the Physical Port Capabilities
	 * to the Advertised Port Capabilities.  Otherwise mark it as
	 * Auto-Negotiate disabled and select the highest supported speed
	 * क्रम the link.  Note parallel काष्ठाure in t4_link_l1cfg_core()
	 * and t4_handle_get_port_info().
	 */
	अगर (lc->pcaps & FW_PORT_CAP32_ANEG) अणु
		lc->acaps = lc->pcaps & ADVERT_MASK;
		lc->स्वतःneg = AUTONEG_ENABLE;
		lc->requested_fc |= PAUSE_AUTONEG;
	पूर्ण अन्यथा अणु
		lc->acaps = 0;
		lc->स्वतःneg = AUTONEG_DISABLE;
	पूर्ण
पूर्ण

अटल व्योम csio_link_l1cfg(काष्ठा link_config *lc, uपूर्णांक16_t fw_caps,
			    uपूर्णांक32_t *rcaps)
अणु
	अचिन्हित पूर्णांक fw_mdi = FW_PORT_CAP32_MDI_V(FW_PORT_CAP32_MDI_AUTO);
	fw_port_cap32_t fw_fc, cc_fec, fw_fec, lrcap;

	lc->link_ok = 0;

	/*
	 * Convert driver coding of Pause Frame Flow Control settings पूर्णांकo the
	 * Firmware's API.
	 */
	fw_fc = cc_to_fwcap_छोड़ो(lc->requested_fc);

	/*
	 * Convert Common Code Forward Error Control settings पूर्णांकo the
	 * Firmware's API.  If the current Requested FEC has "Automatic"
	 * (IEEE 802.3) specअगरied, then we use whatever the Firmware
	 * sent us as part of it's IEEE 802.3-based पूर्णांकerpretation of
	 * the Transceiver Module EPROM FEC parameters.  Otherwise we
	 * use whatever is in the current Requested FEC settings.
	 */
	अगर (lc->requested_fec & FEC_AUTO)
		cc_fec = fwcap_to_cc_fec(lc->def_acaps);
	अन्यथा
		cc_fec = lc->requested_fec;
	fw_fec = cc_to_fwcap_fec(cc_fec);

	/* Figure out what our Requested Port Capabilities are going to be.
	 * Note parallel काष्ठाure in t4_handle_get_port_info() and
	 * init_link_config().
	 */
	अगर (!(lc->pcaps & FW_PORT_CAP32_ANEG)) अणु
		lrcap = (lc->pcaps & ADVERT_MASK) | fw_fc | fw_fec;
		lc->fc = lc->requested_fc & ~PAUSE_AUTONEG;
		lc->fec = cc_fec;
	पूर्ण अन्यथा अगर (lc->स्वतःneg == AUTONEG_DISABLE) अणु
		lrcap = lc->speed_caps | fw_fc | fw_fec | fw_mdi;
		lc->fc = lc->requested_fc & ~PAUSE_AUTONEG;
		lc->fec = cc_fec;
	पूर्ण अन्यथा अणु
		lrcap = lc->acaps | fw_fc | fw_fec | fw_mdi;
	पूर्ण

	*rcaps = lrcap;
पूर्ण

/*
 * csio_enable_ports - Bring up all available ports.
 * @hw: HW module.
 *
 */
अटल पूर्णांक
csio_enable_ports(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mb  *mbp;
	u16 fw_caps = FW_CAPS_UNKNOWN;
	क्रमागत fw_retval retval;
	uपूर्णांक8_t portid;
	fw_port_cap32_t pcaps, acaps, rcaps;
	पूर्णांक i;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < hw->num_pports; i++) अणु
		portid = hw->pport[i].portid;

		अगर (fw_caps == FW_CAPS_UNKNOWN) अणु
			u32 param, val;

			param = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) |
			 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_PORT_CAPS32));
			val = 1;

			csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO,
				       hw->pfn, 0, 1, &param, &val, true,
				       शून्य);

			अगर (csio_mb_issue(hw, mbp)) अणु
				csio_err(hw, "failed to issue FW_PARAMS_CMD(r) port:%d\n",
					 portid);
				mempool_मुक्त(mbp, hw->mb_mempool);
				वापस -EINVAL;
			पूर्ण

			csio_mb_process_पढ़ो_params_rsp(hw, mbp, &retval,
							0, शून्य);
			fw_caps = retval ? FW_CAPS16 : FW_CAPS32;
		पूर्ण

		/* Read PORT inक्रमmation */
		csio_mb_port(hw, mbp, CSIO_MB_DEFAULT_TMO, portid,
			     false, 0, fw_caps, शून्य);

		अगर (csio_mb_issue(hw, mbp)) अणु
			csio_err(hw, "failed to issue FW_PORT_CMD(r) port:%d\n",
				 portid);
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण

		csio_mb_process_पढ़ो_port_rsp(hw, mbp, &retval, fw_caps,
					      &pcaps, &acaps);
		अगर (retval != FW_SUCCESS) अणु
			csio_err(hw, "FW_PORT_CMD(r) port:%d failed: 0x%x\n",
				 portid, retval);
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण

		csio_init_link_config(&hw->pport[i].link_cfg, pcaps, acaps);

		csio_link_l1cfg(&hw->pport[i].link_cfg, fw_caps, &rcaps);

		/* Write back PORT inक्रमmation */
		csio_mb_port(hw, mbp, CSIO_MB_DEFAULT_TMO, portid,
			     true, rcaps, fw_caps, शून्य);

		अगर (csio_mb_issue(hw, mbp)) अणु
			csio_err(hw, "failed to issue FW_PORT_CMD(w) port:%d\n",
				 portid);
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण

		retval = csio_mb_fw_retval(mbp);
		अगर (retval != FW_SUCCESS) अणु
			csio_err(hw, "FW_PORT_CMD(w) port:%d failed :0x%x\n",
				 portid, retval);
			mempool_मुक्त(mbp, hw->mb_mempool);
			वापस -EINVAL;
		पूर्ण

	पूर्ण /* For all ports */

	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

/*
 * csio_get_fcoe_resinfo - Read fcoe fw resource info.
 * @hw: HW module
 * Issued with lock held.
 */
अटल पूर्णांक
csio_get_fcoe_resinfo(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_fcoe_res_info *res_info = &hw->fres_info;
	काष्ठा fw_fcoe_res_info_cmd *rsp;
	काष्ठा csio_mb  *mbp;
	क्रमागत fw_retval retval;

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/* Get FCoE FW resource inक्रमmation */
	csio_fcoe_पढ़ो_res_info_init_mb(hw, mbp, CSIO_MB_DEFAULT_TMO, शून्य);

	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "failed to issue FW_FCOE_RES_INFO_CMD\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	rsp = (काष्ठा fw_fcoe_res_info_cmd *)(mbp->mb);
	retval = FW_CMD_RETVAL_G(ntohl(rsp->retval_len16));
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FW_FCOE_RES_INFO_CMD failed with ret x%x\n",
			 retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	res_info->e_d_tov = ntohs(rsp->e_d_tov);
	res_info->r_a_tov_seq = ntohs(rsp->r_a_tov_seq);
	res_info->r_a_tov_els = ntohs(rsp->r_a_tov_els);
	res_info->r_r_tov = ntohs(rsp->r_r_tov);
	res_info->max_xchgs = ntohl(rsp->max_xchgs);
	res_info->max_ssns = ntohl(rsp->max_ssns);
	res_info->used_xchgs = ntohl(rsp->used_xchgs);
	res_info->used_ssns = ntohl(rsp->used_ssns);
	res_info->max_fcfs = ntohl(rsp->max_fcfs);
	res_info->max_vnps = ntohl(rsp->max_vnps);
	res_info->used_fcfs = ntohl(rsp->used_fcfs);
	res_info->used_vnps = ntohl(rsp->used_vnps);

	csio_dbg(hw, "max ssns:%d max xchgs:%d\n", res_info->max_ssns,
						  res_info->max_xchgs);
	mempool_मुक्त(mbp, hw->mb_mempool);

	वापस 0;
पूर्ण

अटल पूर्णांक
csio_hw_check_fwconfig(काष्ठा csio_hw *hw, u32 *param)
अणु
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;
	u32 _param[1];

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Find out whether we're dealing with a version of
	 * the firmware which has configuration file support.
	 */
	_param[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		     FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_CF));

	csio_mb_params(hw, mbp, CSIO_MB_DEFAULT_TMO, hw->pfn, 0,
		       ARRAY_SIZE(_param), _param, शून्य, false, शून्य);
	अगर (csio_mb_issue(hw, mbp)) अणु
		csio_err(hw, "Issue of FW_PARAMS_CMD(read) failed!\n");
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	csio_mb_process_पढ़ो_params_rsp(hw, mbp, &retval,
			ARRAY_SIZE(_param), _param);
	अगर (retval != FW_SUCCESS) अणु
		csio_err(hw, "FW_PARAMS_CMD(read) failed with ret:0x%x!\n",
				retval);
		mempool_मुक्त(mbp, hw->mb_mempool);
		वापस -EINVAL;
	पूर्ण

	mempool_मुक्त(mbp, hw->mb_mempool);
	*param = _param[0];

	वापस 0;
पूर्ण

अटल पूर्णांक
csio_hw_flash_config(काष्ठा csio_hw *hw, u32 *fw_cfg_param, अक्षर *path)
अणु
	पूर्णांक ret = 0;
	स्थिर काष्ठा firmware *cf;
	काष्ठा pci_dev *pci_dev = hw->pdev;
	काष्ठा device *dev = &pci_dev->dev;
	अचिन्हित पूर्णांक mtype = 0, maddr = 0;
	uपूर्णांक32_t *cfg_data;
	पूर्णांक value_to_add = 0;
	स्थिर अक्षर *fw_cfg_file;

	अगर (csio_is_t5(pci_dev->device & CSIO_HW_CHIP_MASK))
		fw_cfg_file = FW_CFG_NAME_T5;
	अन्यथा
		fw_cfg_file = FW_CFG_NAME_T6;

	अगर (request_firmware(&cf, fw_cfg_file, dev) < 0) अणु
		csio_err(hw, "could not find config file %s, err: %d\n",
			 fw_cfg_file, ret);
		वापस -ENOENT;
	पूर्ण

	अगर (cf->size%4 != 0)
		value_to_add = 4 - (cf->size % 4);

	cfg_data = kzalloc(cf->size+value_to_add, GFP_KERNEL);
	अगर (cfg_data == शून्य) अणु
		ret = -ENOMEM;
		जाओ leave;
	पूर्ण

	स_नकल((व्योम *)cfg_data, (स्थिर व्योम *)cf->data, cf->size);
	अगर (csio_hw_check_fwconfig(hw, fw_cfg_param) != 0) अणु
		ret = -EINVAL;
		जाओ leave;
	पूर्ण

	mtype = FW_PARAMS_PARAM_Y_G(*fw_cfg_param);
	maddr = FW_PARAMS_PARAM_Z_G(*fw_cfg_param) << 16;

	ret = csio_memory_ग_लिखो(hw, mtype, maddr,
				cf->size + value_to_add, cfg_data);

	अगर ((ret == 0) && (value_to_add != 0)) अणु
		जोड़ अणु
			u32 word;
			अक्षर buf[4];
		पूर्ण last;
		माप_प्रकार size = cf->size & ~0x3;
		पूर्णांक i;

		last.word = cfg_data[size >> 2];
		क्रम (i = value_to_add; i < 4; i++)
			last.buf[i] = 0;
		ret = csio_memory_ग_लिखो(hw, mtype, maddr + size, 4, &last.word);
	पूर्ण
	अगर (ret == 0) अणु
		csio_info(hw, "config file upgraded to %s\n", fw_cfg_file);
		snम_लिखो(path, 64, "%s%s", "/lib/firmware/", fw_cfg_file);
	पूर्ण

leave:
	kमुक्त(cfg_data);
	release_firmware(cf);
	वापस ret;
पूर्ण

/*
 * HW initialization: contact FW, obtain config, perक्रमm basic init.
 *
 * If the firmware we're dealing with has Configuration File support, then
 * we use that to perक्रमm all configuration -- either using the configuration
 * file stored in flash on the adapter or using a fileप्रणाली-local file
 * अगर available.
 *
 * If we करोn't have configuration file support in the firmware, then we'll
 * have to set things up the old fashioned way with hard-coded रेजिस्टर
 * ग_लिखोs and firmware commands ...
 */

/*
 * Attempt to initialize the HW via a Firmware Configuration File.
 */
अटल पूर्णांक
csio_hw_use_fwconfig(काष्ठा csio_hw *hw, पूर्णांक reset, u32 *fw_cfg_param)
अणु
	काष्ठा csio_mb	*mbp = शून्य;
	काष्ठा fw_caps_config_cmd *caps_cmd;
	अचिन्हित पूर्णांक mtype, maddr;
	पूर्णांक rv = -EINVAL;
	uपूर्णांक32_t finiver = 0, finicsum = 0, cfcsum = 0;
	अक्षर path[64];
	अक्षर *config_name = शून्य;

	/*
	 * Reset device अगर necessary
	 */
	अगर (reset) अणु
		rv = csio_करो_reset(hw, true);
		अगर (rv != 0)
			जाओ bye;
	पूर्ण

	/*
	 * If we have a configuration file in host ,
	 * then use that.  Otherwise, use the configuration file stored
	 * in the HW flash ...
	 */
	spin_unlock_irq(&hw->lock);
	rv = csio_hw_flash_config(hw, fw_cfg_param, path);
	spin_lock_irq(&hw->lock);
	अगर (rv != 0) अणु
		/*
		 * config file was not found. Use शेष
		 * config file from flash.
		 */
		config_name = "On FLASH";
		mtype = FW_MEMTYPE_CF_FLASH;
		maddr = hw->chip_ops->chip_flash_cfg_addr(hw);
	पूर्ण अन्यथा अणु
		config_name = path;
		mtype = FW_PARAMS_PARAM_Y_G(*fw_cfg_param);
		maddr = FW_PARAMS_PARAM_Z_G(*fw_cfg_param) << 16;
	पूर्ण

	mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
	अगर (!mbp) अणु
		CSIO_INC_STATS(hw, n_err_nomem);
		वापस -ENOMEM;
	पूर्ण
	/*
	 * Tell the firmware to process the indicated Configuration File.
	 * If there are no errors and the caller has provided वापस value
	 * poपूर्णांकers क्रम the [fini] section version, checksum and computed
	 * checksum, pass those back to the caller.
	 */
	caps_cmd = (काष्ठा fw_caps_config_cmd *)(mbp->mb);
	CSIO_INIT_MBP(mbp, caps_cmd, CSIO_MB_DEFAULT_TMO, hw, शून्य, 1);
	caps_cmd->op_to_ग_लिखो =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_READ_F);
	caps_cmd->cfvalid_to_len16 =
		htonl(FW_CAPS_CONFIG_CMD_CFVALID_F |
		      FW_CAPS_CONFIG_CMD_MEMTYPE_CF_V(mtype) |
		      FW_CAPS_CONFIG_CMD_MEMADDR64K_CF_V(maddr >> 16) |
		      FW_LEN16(*caps_cmd));

	अगर (csio_mb_issue(hw, mbp)) अणु
		rv = -EINVAL;
		जाओ bye;
	पूर्ण

	rv = csio_mb_fw_retval(mbp);
	 /* If the CAPS_CONFIG failed with an ENOENT (क्रम a Firmware
	  * Configuration File in FLASH), our last gasp efक्रमt is to use the
	  * Firmware Configuration File which is embedded in the
	  * firmware.  A very few early versions of the firmware didn't
	  * have one embedded but we can ignore those.
	  */
	अगर (rv == ENOENT) अणु
		CSIO_INIT_MBP(mbp, caps_cmd, CSIO_MB_DEFAULT_TMO, hw, शून्य, 1);
		caps_cmd->op_to_ग_लिखो = htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
					      FW_CMD_REQUEST_F |
					      FW_CMD_READ_F);
		caps_cmd->cfvalid_to_len16 = htonl(FW_LEN16(*caps_cmd));

		अगर (csio_mb_issue(hw, mbp)) अणु
			rv = -EINVAL;
			जाओ bye;
		पूर्ण

		rv = csio_mb_fw_retval(mbp);
		config_name = "Firmware Default";
	पूर्ण
	अगर (rv != FW_SUCCESS)
		जाओ bye;

	finiver = ntohl(caps_cmd->finiver);
	finicsum = ntohl(caps_cmd->finicsum);
	cfcsum = ntohl(caps_cmd->cfcsum);

	/*
	 * And now tell the firmware to use the configuration we just loaded.
	 */
	caps_cmd->op_to_ग_लिखो =
		htonl(FW_CMD_OP_V(FW_CAPS_CONFIG_CMD) |
		      FW_CMD_REQUEST_F |
		      FW_CMD_WRITE_F);
	caps_cmd->cfvalid_to_len16 = htonl(FW_LEN16(*caps_cmd));

	अगर (csio_mb_issue(hw, mbp)) अणु
		rv = -EINVAL;
		जाओ bye;
	पूर्ण

	rv = csio_mb_fw_retval(mbp);
	अगर (rv != FW_SUCCESS) अणु
		csio_dbg(hw, "FW_CAPS_CONFIG_CMD returned %d!\n", rv);
		जाओ bye;
	पूर्ण

	अगर (finicsum != cfcsum) अणु
		csio_warn(hw,
		      "Config File checksum mismatch: csum=%#x, computed=%#x\n",
		      finicsum, cfcsum);
	पूर्ण

	/* Validate device capabilities */
	rv = csio_hw_validate_caps(hw, mbp);
	अगर (rv != 0)
		जाओ bye;

	mempool_मुक्त(mbp, hw->mb_mempool);
	mbp = शून्य;

	/*
	 * Note that we're operating with parameters
	 * not supplied by the driver, rather than from hard-wired
	 * initialization स्थिरants buried in the driver.
	 */
	hw->flags |= CSIO_HWF_USING_SOFT_PARAMS;

	/* device parameters */
	rv = csio_get_device_params(hw);
	अगर (rv != 0)
		जाओ bye;

	/* Configure SGE */
	csio_wr_sge_init(hw);

	/*
	 * And finally tell the firmware to initialize itself using the
	 * parameters from the Configuration File.
	 */
	/* Post event to notअगरy completion of configuration */
	csio_post_event(&hw->sm, CSIO_HWE_INIT);

	csio_info(hw, "Successfully configure using Firmware "
		  "Configuration File %s, version %#x, computed checksum %#x\n",
		  config_name, finiver, cfcsum);
	वापस 0;

	/*
	 * Something bad happened.  Return the error ...
	 */
bye:
	अगर (mbp)
		mempool_मुक्त(mbp, hw->mb_mempool);
	hw->flags &= ~CSIO_HWF_USING_SOFT_PARAMS;
	csio_warn(hw, "Configuration file error %d\n", rv);
	वापस rv;
पूर्ण

/* Is the given firmware API compatible with the one the driver was compiled
 * with?
 */
अटल पूर्णांक fw_compatible(स्थिर काष्ठा fw_hdr *hdr1, स्थिर काष्ठा fw_hdr *hdr2)
अणु

	/* लघु circuit अगर it's the exact same firmware version */
	अगर (hdr1->chip == hdr2->chip && hdr1->fw_ver == hdr2->fw_ver)
		वापस 1;

#घोषणा SAME_INTF(x) (hdr1->पूर्णांकfver_##x == hdr2->पूर्णांकfver_##x)
	अगर (hdr1->chip == hdr2->chip && SAME_INTF(nic) && SAME_INTF(vnic) &&
	    SAME_INTF(ri) && SAME_INTF(iscsi) && SAME_INTF(fcoe))
		वापस 1;
#अघोषित SAME_INTF

	वापस 0;
पूर्ण

/* The firmware in the fileप्रणाली is usable, but should it be installed?
 * This routine explains itself in detail अगर it indicates the fileप्रणाली
 * firmware should be installed.
 */
अटल पूर्णांक csio_should_install_fs_fw(काष्ठा csio_hw *hw, पूर्णांक card_fw_usable,
				पूर्णांक k, पूर्णांक c)
अणु
	स्थिर अक्षर *reason;

	अगर (!card_fw_usable) अणु
		reason = "incompatible or unusable";
		जाओ install;
	पूर्ण

	अगर (k > c) अणु
		reason = "older than the version supported with this driver";
		जाओ install;
	पूर्ण

	वापस 0;

install:
	csio_err(hw, "firmware on card (%u.%u.%u.%u) is %s, "
		"installing firmware %u.%u.%u.%u on card.\n",
		FW_HDR_FW_VER_MAJOR_G(c), FW_HDR_FW_VER_MINOR_G(c),
		FW_HDR_FW_VER_MICRO_G(c), FW_HDR_FW_VER_BUILD_G(c), reason,
		FW_HDR_FW_VER_MAJOR_G(k), FW_HDR_FW_VER_MINOR_G(k),
		FW_HDR_FW_VER_MICRO_G(k), FW_HDR_FW_VER_BUILD_G(k));

	वापस 1;
पूर्ण

अटल काष्ठा fw_info fw_info_array[] = अणु
	अणु
		.chip = CHELSIO_T5,
		.fs_name = FW_CFG_NAME_T5,
		.fw_mod_name = FW_FNAME_T5,
		.fw_hdr = अणु
			.chip = FW_HDR_CHIP_T5,
			.fw_ver = __cpu_to_be32(FW_VERSION(T5)),
			.पूर्णांकfver_nic = FW_INTFVER(T5, NIC),
			.पूर्णांकfver_vnic = FW_INTFVER(T5, VNIC),
			.पूर्णांकfver_ri = FW_INTFVER(T5, RI),
			.पूर्णांकfver_iscsi = FW_INTFVER(T5, ISCSI),
			.पूर्णांकfver_fcoe = FW_INTFVER(T5, FCOE),
		पूर्ण,
	पूर्ण, अणु
		.chip = CHELSIO_T6,
		.fs_name = FW_CFG_NAME_T6,
		.fw_mod_name = FW_FNAME_T6,
		.fw_hdr = अणु
			.chip = FW_HDR_CHIP_T6,
			.fw_ver = __cpu_to_be32(FW_VERSION(T6)),
			.पूर्णांकfver_nic = FW_INTFVER(T6, NIC),
			.पूर्णांकfver_vnic = FW_INTFVER(T6, VNIC),
			.पूर्णांकfver_ri = FW_INTFVER(T6, RI),
			.पूर्णांकfver_iscsi = FW_INTFVER(T6, ISCSI),
			.पूर्णांकfver_fcoe = FW_INTFVER(T6, FCOE),
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा fw_info *find_fw_info(पूर्णांक chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fw_info_array); i++) अणु
		अगर (fw_info_array[i].chip == chip)
			वापस &fw_info_array[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक csio_hw_prep_fw(काष्ठा csio_hw *hw, काष्ठा fw_info *fw_info,
	       स्थिर u8 *fw_data, अचिन्हित पूर्णांक fw_size,
	       काष्ठा fw_hdr *card_fw, क्रमागत csio_dev_state state,
	       पूर्णांक *reset)
अणु
	पूर्णांक ret, card_fw_usable, fs_fw_usable;
	स्थिर काष्ठा fw_hdr *fs_fw;
	स्थिर काष्ठा fw_hdr *drv_fw;

	drv_fw = &fw_info->fw_hdr;

	/* Read the header of the firmware on the card */
	ret = csio_hw_पढ़ो_flash(hw, FLASH_FW_START,
			    माप(*card_fw) / माप(uपूर्णांक32_t),
			    (uपूर्णांक32_t *)card_fw, 1);
	अगर (ret == 0) अणु
		card_fw_usable = fw_compatible(drv_fw, (स्थिर व्योम *)card_fw);
	पूर्ण अन्यथा अणु
		csio_err(hw,
			"Unable to read card's firmware header: %d\n", ret);
		card_fw_usable = 0;
	पूर्ण

	अगर (fw_data != शून्य) अणु
		fs_fw = (स्थिर व्योम *)fw_data;
		fs_fw_usable = fw_compatible(drv_fw, fs_fw);
	पूर्ण अन्यथा अणु
		fs_fw = शून्य;
		fs_fw_usable = 0;
	पूर्ण

	अगर (card_fw_usable && card_fw->fw_ver == drv_fw->fw_ver &&
	    (!fs_fw_usable || fs_fw->fw_ver == drv_fw->fw_ver)) अणु
		/* Common हाल: the firmware on the card is an exact match and
		 * the fileप्रणाली one is an exact match too, or the fileप्रणाली
		 * one is असलent/incompatible.
		 */
	पूर्ण अन्यथा अगर (fs_fw_usable && state == CSIO_DEV_STATE_UNINIT &&
		   csio_should_install_fs_fw(hw, card_fw_usable,
					be32_to_cpu(fs_fw->fw_ver),
					be32_to_cpu(card_fw->fw_ver))) अणु
		ret = csio_hw_fw_upgrade(hw, hw->pfn, fw_data,
				     fw_size, 0);
		अगर (ret != 0) अणु
			csio_err(hw,
				"failed to install firmware: %d\n", ret);
			जाओ bye;
		पूर्ण

		/* Installed successfully, update the cached header too. */
		स_नकल(card_fw, fs_fw, माप(*card_fw));
		card_fw_usable = 1;
		*reset = 0;	/* alपढ़ोy reset as part of load_fw */
	पूर्ण

	अगर (!card_fw_usable) अणु
		uपूर्णांक32_t d, c, k;

		d = be32_to_cpu(drv_fw->fw_ver);
		c = be32_to_cpu(card_fw->fw_ver);
		k = fs_fw ? be32_to_cpu(fs_fw->fw_ver) : 0;

		csio_err(hw, "Cannot find a usable firmware: "
			"chip state %d, "
			"driver compiled with %d.%d.%d.%d, "
			"card has %d.%d.%d.%d, filesystem has %d.%d.%d.%d\n",
			state,
			FW_HDR_FW_VER_MAJOR_G(d), FW_HDR_FW_VER_MINOR_G(d),
			FW_HDR_FW_VER_MICRO_G(d), FW_HDR_FW_VER_BUILD_G(d),
			FW_HDR_FW_VER_MAJOR_G(c), FW_HDR_FW_VER_MINOR_G(c),
			FW_HDR_FW_VER_MICRO_G(c), FW_HDR_FW_VER_BUILD_G(c),
			FW_HDR_FW_VER_MAJOR_G(k), FW_HDR_FW_VER_MINOR_G(k),
			FW_HDR_FW_VER_MICRO_G(k), FW_HDR_FW_VER_BUILD_G(k));
		ret = -EINVAL;
		जाओ bye;
	पूर्ण

	/* We're using whatever's on the card and it's known to be good. */
	hw->fwrev = be32_to_cpu(card_fw->fw_ver);
	hw->tp_vers = be32_to_cpu(card_fw->tp_microcode_ver);

bye:
	वापस ret;
पूर्ण

/*
 * Returns -EINVAL अगर attempts to flash the firmware failed,
 * -ENOMEM अगर memory allocation failed अन्यथा वापसs 0,
 * अगर flashing was not attempted because the card had the
 * latest firmware ECANCELED is वापसed
 */
अटल पूर्णांक
csio_hw_flash_fw(काष्ठा csio_hw *hw, पूर्णांक *reset)
अणु
	पूर्णांक ret = -ECANCELED;
	स्थिर काष्ठा firmware *fw;
	काष्ठा fw_info *fw_info;
	काष्ठा fw_hdr *card_fw;
	काष्ठा pci_dev *pci_dev = hw->pdev;
	काष्ठा device *dev = &pci_dev->dev ;
	स्थिर u8 *fw_data = शून्य;
	अचिन्हित पूर्णांक fw_size = 0;
	स्थिर अक्षर *fw_bin_file;

	/* This is the firmware whose headers the driver was compiled
	 * against
	 */
	fw_info = find_fw_info(CHELSIO_CHIP_VERSION(hw->chip_id));
	अगर (fw_info == शून्य) अणु
		csio_err(hw,
			"unable to get firmware info for chip %d.\n",
			CHELSIO_CHIP_VERSION(hw->chip_id));
		वापस -EINVAL;
	पूर्ण

	/* allocate memory to पढ़ो the header of the firmware on the
	 * card
	 */
	card_fw = kदो_स्मृति(माप(*card_fw), GFP_KERNEL);
	अगर (!card_fw)
		वापस -ENOMEM;

	अगर (csio_is_t5(pci_dev->device & CSIO_HW_CHIP_MASK))
		fw_bin_file = FW_FNAME_T5;
	अन्यथा
		fw_bin_file = FW_FNAME_T6;

	अगर (request_firmware(&fw, fw_bin_file, dev) < 0) अणु
		csio_err(hw, "could not find firmware image %s, err: %d\n",
			 fw_bin_file, ret);
	पूर्ण अन्यथा अणु
		fw_data = fw->data;
		fw_size = fw->size;
	पूर्ण

	/* upgrade FW logic */
	ret = csio_hw_prep_fw(hw, fw_info, fw_data, fw_size, card_fw,
			 hw->fw_state, reset);

	/* Cleaning up */
	अगर (fw != शून्य)
		release_firmware(fw);
	kमुक्त(card_fw);
	वापस ret;
पूर्ण

अटल पूर्णांक csio_hw_check_fwver(काष्ठा csio_hw *hw)
अणु
	अगर (csio_is_t6(hw->pdev->device & CSIO_HW_CHIP_MASK) &&
	    (hw->fwrev < CSIO_MIN_T6_FW)) अणु
		csio_hw_prपूर्णांक_fw_version(hw, "T6 unsupported fw");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * csio_hw_configure - Configure HW
 * @hw - HW module
 *
 */
अटल व्योम
csio_hw_configure(काष्ठा csio_hw *hw)
अणु
	पूर्णांक reset = 1;
	पूर्णांक rv;
	u32 param[1];

	rv = csio_hw_dev_पढ़ोy(hw);
	अगर (rv != 0) अणु
		CSIO_INC_STATS(hw, n_err_fatal);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		जाओ out;
	पूर्ण

	/* HW version */
	hw->chip_ver = (अक्षर)csio_rd_reg32(hw, PL_REV_A);

	/* Needed क्रम FW करोwnload */
	rv = csio_hw_get_flash_params(hw);
	अगर (rv != 0) अणु
		csio_err(hw, "Failed to get serial flash params rv:%d\n", rv);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		जाओ out;
	पूर्ण

	/* Set PCIe completion समयout to 4 seconds */
	अगर (pci_is_pcie(hw->pdev))
		pcie_capability_clear_and_set_word(hw->pdev, PCI_EXP_DEVCTL2,
				PCI_EXP_DEVCTL2_COMP_TIMEOUT, 0xd);

	hw->chip_ops->chip_set_mem_win(hw, MEMWIN_CSIOSTOR);

	rv = csio_hw_get_fw_version(hw, &hw->fwrev);
	अगर (rv != 0)
		जाओ out;

	csio_hw_prपूर्णांक_fw_version(hw, "Firmware revision");

	rv = csio_करो_hello(hw, &hw->fw_state);
	अगर (rv != 0) अणु
		CSIO_INC_STATS(hw, n_err_fatal);
		csio_post_event(&hw->sm, CSIO_HWE_FATAL);
		जाओ out;
	पूर्ण

	/* Read vpd */
	rv = csio_hw_get_vpd_params(hw, &hw->vpd);
	अगर (rv != 0)
		जाओ out;

	csio_hw_get_fw_version(hw, &hw->fwrev);
	csio_hw_get_tp_version(hw, &hw->tp_vers);
	अगर (csio_is_hw_master(hw) && hw->fw_state != CSIO_DEV_STATE_INIT) अणु

			/* Do firmware update */
		spin_unlock_irq(&hw->lock);
		rv = csio_hw_flash_fw(hw, &reset);
		spin_lock_irq(&hw->lock);

		अगर (rv != 0)
			जाओ out;

		rv = csio_hw_check_fwver(hw);
		अगर (rv < 0)
			जाओ out;

		/* If the firmware करोesn't support Configuration Files,
		 * वापस an error.
		 */
		rv = csio_hw_check_fwconfig(hw, param);
		अगर (rv != 0) अणु
			csio_info(hw, "Firmware doesn't support "
				  "Firmware Configuration files\n");
			जाओ out;
		पूर्ण

		/* The firmware provides us with a memory buffer where we can
		 * load a Configuration File from the host अगर we want to
		 * override the Configuration File in flash.
		 */
		rv = csio_hw_use_fwconfig(hw, reset, param);
		अगर (rv == -ENOENT) अणु
			csio_info(hw, "Could not initialize "
				  "adapter, error%d\n", rv);
			जाओ out;
		पूर्ण
		अगर (rv != 0) अणु
			csio_info(hw, "Could not initialize "
				  "adapter, error%d\n", rv);
			जाओ out;
		पूर्ण

	पूर्ण अन्यथा अणु
		rv = csio_hw_check_fwver(hw);
		अगर (rv < 0)
			जाओ out;

		अगर (hw->fw_state == CSIO_DEV_STATE_INIT) अणु

			hw->flags |= CSIO_HWF_USING_SOFT_PARAMS;

			/* device parameters */
			rv = csio_get_device_params(hw);
			अगर (rv != 0)
				जाओ out;

			/* Get device capabilities */
			rv = csio_config_device_caps(hw);
			अगर (rv != 0)
				जाओ out;

			/* Configure SGE */
			csio_wr_sge_init(hw);

			/* Post event to notअगरy completion of configuration */
			csio_post_event(&hw->sm, CSIO_HWE_INIT);
			जाओ out;
		पूर्ण
	पूर्ण /* अगर not master */

out:
	वापस;
पूर्ण

/*
 * csio_hw_initialize - Initialize HW
 * @hw - HW module
 *
 */
अटल व्योम
csio_hw_initialize(काष्ठा csio_hw *hw)
अणु
	काष्ठा csio_mb	*mbp;
	क्रमागत fw_retval retval;
	पूर्णांक rv;
	पूर्णांक i;

	अगर (csio_is_hw_master(hw) && hw->fw_state != CSIO_DEV_STATE_INIT) अणु
		mbp = mempool_alloc(hw->mb_mempool, GFP_ATOMIC);
		अगर (!mbp)
			जाओ out;

		csio_mb_initialize(hw, mbp, CSIO_MB_DEFAULT_TMO, शून्य);

		अगर (csio_mb_issue(hw, mbp)) अणु
			csio_err(hw, "Issue of FW_INITIALIZE_CMD failed!\n");
			जाओ मुक्त_and_out;
		पूर्ण

		retval = csio_mb_fw_retval(mbp);
		अगर (retval != FW_SUCCESS) अणु
			csio_err(hw, "FW_INITIALIZE_CMD returned 0x%x!\n",
				 retval);
			जाओ मुक्त_and_out;
		पूर्ण

		mempool_मुक्त(mbp, hw->mb_mempool);
	पूर्ण

	rv = csio_get_fcoe_resinfo(hw);
	अगर (rv != 0) अणु
		csio_err(hw, "Failed to read fcoe resource info: %d\n", rv);
		जाओ out;
	पूर्ण

	spin_unlock_irq(&hw->lock);
	rv = csio_config_queues(hw);
	spin_lock_irq(&hw->lock);

	अगर (rv != 0) अणु
		csio_err(hw, "Config of queues failed!: %d\n", rv);
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < hw->num_pports; i++)
		hw->pport[i].mod_type = FW_PORT_MOD_TYPE_NA;

	अगर (csio_is_hw_master(hw) && hw->fw_state != CSIO_DEV_STATE_INIT) अणु
		rv = csio_enable_ports(hw);
		अगर (rv != 0) अणु
			csio_err(hw, "Failed to enable ports: %d\n", rv);
			जाओ out;
		पूर्ण
	पूर्ण

	csio_post_event(&hw->sm, CSIO_HWE_INIT_DONE);
	वापस;

मुक्त_and_out:
	mempool_मुक्त(mbp, hw->mb_mempool);
out:
	वापस;
पूर्ण

#घोषणा PF_INTR_MASK (PFSW_F | PFCIM_F)

/*
 * csio_hw_पूर्णांकr_enable - Enable HW पूर्णांकerrupts
 * @hw: Poपूर्णांकer to HW module.
 *
 * Enable पूर्णांकerrupts in HW रेजिस्टरs.
 */
अटल व्योम
csio_hw_पूर्णांकr_enable(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक16_t vec = (uपूर्णांक16_t)csio_get_mb_पूर्णांकr_idx(csio_hw_to_mbm(hw));
	u32 pf = 0;
	uपूर्णांक32_t pl = csio_rd_reg32(hw, PL_INT_ENABLE_A);

	अगर (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		pf = SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));
	अन्यथा
		pf = T6_SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));

	/*
	 * Set aivec क्रम MSI/MSIX. PCIE_PF_CFG.INTXType is set up
	 * by FW, so करो nothing क्रम INTX.
	 */
	अगर (hw->पूर्णांकr_mode == CSIO_IM_MSIX)
		csio_set_reg_field(hw, MYPF_REG(PCIE_PF_CFG_A),
				   AIVEC_V(AIVEC_M), vec);
	अन्यथा अगर (hw->पूर्णांकr_mode == CSIO_IM_MSI)
		csio_set_reg_field(hw, MYPF_REG(PCIE_PF_CFG_A),
				   AIVEC_V(AIVEC_M), 0);

	csio_wr_reg32(hw, PF_INTR_MASK, MYPF_REG(PL_PF_INT_ENABLE_A));

	/* Turn on MB पूर्णांकerrupts - this will पूर्णांकernally flush PIO as well */
	csio_mb_पूर्णांकr_enable(hw);

	/* These are common रेजिस्टरs - only a master can modअगरy them */
	अगर (csio_is_hw_master(hw)) अणु
		/*
		 * Disable the Serial FLASH पूर्णांकerrupt, अगर enabled!
		 */
		pl &= (~SF_F);
		csio_wr_reg32(hw, pl, PL_INT_ENABLE_A);

		csio_wr_reg32(hw, ERR_CPL_EXCEED_IQE_SIZE_F |
			      EGRESS_SIZE_ERR_F | ERR_INVALID_CIDX_INC_F |
			      ERR_CPL_OPCODE_0_F | ERR_DROPPED_DB_F |
			      ERR_DATA_CPL_ON_HIGH_QID1_F |
			      ERR_DATA_CPL_ON_HIGH_QID0_F | ERR_BAD_DB_PIDX3_F |
			      ERR_BAD_DB_PIDX2_F | ERR_BAD_DB_PIDX1_F |
			      ERR_BAD_DB_PIDX0_F | ERR_ING_CTXT_PRIO_F |
			      ERR_EGR_CTXT_PRIO_F | INGRESS_SIZE_ERR_F,
			      SGE_INT_ENABLE3_A);
		csio_set_reg_field(hw, PL_INT_MAP0_A, 0, 1 << pf);
	पूर्ण

	hw->flags |= CSIO_HWF_HW_INTR_ENABLED;

पूर्ण

/*
 * csio_hw_पूर्णांकr_disable - Disable HW पूर्णांकerrupts
 * @hw: Poपूर्णांकer to HW module.
 *
 * Turn off Mailbox and PCI_PF_CFG पूर्णांकerrupts.
 */
व्योम
csio_hw_पूर्णांकr_disable(काष्ठा csio_hw *hw)
अणु
	u32 pf = 0;

	अगर (csio_is_t5(hw->pdev->device & CSIO_HW_CHIP_MASK))
		pf = SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));
	अन्यथा
		pf = T6_SOURCEPF_G(csio_rd_reg32(hw, PL_WHOAMI_A));

	अगर (!(hw->flags & CSIO_HWF_HW_INTR_ENABLED))
		वापस;

	hw->flags &= ~CSIO_HWF_HW_INTR_ENABLED;

	csio_wr_reg32(hw, 0, MYPF_REG(PL_PF_INT_ENABLE_A));
	अगर (csio_is_hw_master(hw))
		csio_set_reg_field(hw, PL_INT_MAP0_A, 1 << pf, 0);

	/* Turn off MB पूर्णांकerrupts */
	csio_mb_पूर्णांकr_disable(hw);

पूर्ण

व्योम
csio_hw_fatal_err(काष्ठा csio_hw *hw)
अणु
	csio_set_reg_field(hw, SGE_CONTROL_A, GLOBALENABLE_F, 0);
	csio_hw_पूर्णांकr_disable(hw);

	/* Do not reset HW, we may need FW state क्रम debugging */
	csio_fatal(hw, "HW Fatal error encountered!\n");
पूर्ण

/*****************************************************************************/
/* START: HW SM                                                              */
/*****************************************************************************/
/*
 * csio_hws_uninit - Uninit state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_uninit(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_CFG:
		csio_set_state(&hw->sm, csio_hws_configuring);
		csio_hw_configure(hw);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_configuring - Configuring state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_configuring(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_INIT:
		csio_set_state(&hw->sm, csio_hws_initializing);
		csio_hw_initialize(hw);
		अवरोध;

	हाल CSIO_HWE_INIT_DONE:
		csio_set_state(&hw->sm, csio_hws_पढ़ोy);
		/* Fan out event to all lnode SMs */
		csio_notअगरy_lnodes(hw, CSIO_LN_NOTIFY_HWREADY);
		अवरोध;

	हाल CSIO_HWE_FATAL:
		csio_set_state(&hw->sm, csio_hws_uninit);
		अवरोध;

	हाल CSIO_HWE_PCI_REMOVE:
		csio_करो_bye(hw);
		अवरोध;
	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_initializing - Initializing state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_initializing(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_INIT_DONE:
		csio_set_state(&hw->sm, csio_hws_पढ़ोy);

		/* Fan out event to all lnode SMs */
		csio_notअगरy_lnodes(hw, CSIO_LN_NOTIFY_HWREADY);

		/* Enable पूर्णांकerrupts */
		csio_hw_पूर्णांकr_enable(hw);
		अवरोध;

	हाल CSIO_HWE_FATAL:
		csio_set_state(&hw->sm, csio_hws_uninit);
		अवरोध;

	हाल CSIO_HWE_PCI_REMOVE:
		csio_करो_bye(hw);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_पढ़ोy - Ready state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_पढ़ोy(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	/* Remember the event */
	hw->evtflag = evt;

	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_HBA_RESET:
	हाल CSIO_HWE_FW_DLOAD:
	हाल CSIO_HWE_SUSPEND:
	हाल CSIO_HWE_PCI_REMOVE:
	हाल CSIO_HWE_PCIERR_DETECTED:
		csio_set_state(&hw->sm, csio_hws_quiescing);
		/* cleanup all outstanding cmds */
		अगर (evt == CSIO_HWE_HBA_RESET ||
		    evt == CSIO_HWE_PCIERR_DETECTED)
			csio_scsim_cleanup_io(csio_hw_to_scsim(hw), false);
		अन्यथा
			csio_scsim_cleanup_io(csio_hw_to_scsim(hw), true);

		csio_hw_पूर्णांकr_disable(hw);
		csio_hw_mbm_cleanup(hw);
		csio_evtq_stop(hw);
		csio_notअगरy_lnodes(hw, CSIO_LN_NOTIFY_HWSTOP);
		csio_evtq_flush(hw);
		csio_mgmपंचांग_cleanup(csio_hw_to_mgmपंचांग(hw));
		csio_post_event(&hw->sm, CSIO_HWE_QUIESCED);
		अवरोध;

	हाल CSIO_HWE_FATAL:
		csio_set_state(&hw->sm, csio_hws_uninit);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_quiescing - Quiescing state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_quiescing(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_QUIESCED:
		चयन (hw->evtflag) अणु
		हाल CSIO_HWE_FW_DLOAD:
			csio_set_state(&hw->sm, csio_hws_resetting);
			/* Download firmware */
			fallthrough;

		हाल CSIO_HWE_HBA_RESET:
			csio_set_state(&hw->sm, csio_hws_resetting);
			/* Start reset of the HBA */
			csio_notअगरy_lnodes(hw, CSIO_LN_NOTIFY_HWRESET);
			csio_wr_destroy_queues(hw, false);
			csio_करो_reset(hw, false);
			csio_post_event(&hw->sm, CSIO_HWE_HBA_RESET_DONE);
			अवरोध;

		हाल CSIO_HWE_PCI_REMOVE:
			csio_set_state(&hw->sm, csio_hws_removing);
			csio_notअगरy_lnodes(hw, CSIO_LN_NOTIFY_HWREMOVE);
			csio_wr_destroy_queues(hw, true);
			/* Now send the bye command */
			csio_करो_bye(hw);
			अवरोध;

		हाल CSIO_HWE_SUSPEND:
			csio_set_state(&hw->sm, csio_hws_quiesced);
			अवरोध;

		हाल CSIO_HWE_PCIERR_DETECTED:
			csio_set_state(&hw->sm, csio_hws_pcierr);
			csio_wr_destroy_queues(hw, false);
			अवरोध;

		शेष:
			CSIO_INC_STATS(hw, n_evt_unexp);
			अवरोध;

		पूर्ण
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_quiesced - Quiesced state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_quiesced(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_RESUME:
		csio_set_state(&hw->sm, csio_hws_configuring);
		csio_hw_configure(hw);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_resetting - HW Resetting state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_resetting(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_HBA_RESET_DONE:
		csio_evtq_start(hw);
		csio_set_state(&hw->sm, csio_hws_configuring);
		csio_hw_configure(hw);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * csio_hws_removing - PCI Hotplug removing state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_removing(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_HBA_RESET:
		अगर (!csio_is_hw_master(hw))
			अवरोध;
		/*
		 * The BYE should have alपढ़ोy been issued, so we can't
		 * use the mailbox पूर्णांकerface. Hence we use the PL_RST
		 * रेजिस्टर directly.
		 */
		csio_err(hw, "Resetting HW and waiting 2 seconds...\n");
		csio_wr_reg32(hw, PIORSTMODE_F | PIORST_F, PL_RST_A);
		mdelay(2000);
		अवरोध;

	/* Should never receive any new events */
	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;

	पूर्ण
पूर्ण

/*
 * csio_hws_pcierr - PCI Error state
 * @hw - HW module
 * @evt - Event
 *
 */
अटल व्योम
csio_hws_pcierr(काष्ठा csio_hw *hw, क्रमागत csio_hw_ev evt)
अणु
	hw->prev_evt = hw->cur_evt;
	hw->cur_evt = evt;
	CSIO_INC_STATS(hw, n_evt_sm[evt]);

	चयन (evt) अणु
	हाल CSIO_HWE_PCIERR_SLOT_RESET:
		csio_evtq_start(hw);
		csio_set_state(&hw->sm, csio_hws_configuring);
		csio_hw_configure(hw);
		अवरोध;

	शेष:
		CSIO_INC_STATS(hw, n_evt_unexp);
		अवरोध;
	पूर्ण
पूर्ण

/*****************************************************************************/
/* END: HW SM                                                                */
/*****************************************************************************/

/*
 *	csio_handle_पूर्णांकr_status - table driven पूर्णांकerrupt handler
 *	@hw: HW instance
 *	@reg: the पूर्णांकerrupt status रेजिस्टर to process
 *	@acts: table of पूर्णांकerrupt actions
 *
 *	A table driven पूर्णांकerrupt handler that applies a set of masks to an
 *	पूर्णांकerrupt status word and perक्रमms the corresponding actions अगर the
 *	पूर्णांकerrupts described by the mask have occurred.  The actions include
 *	optionally emitting a warning or alert message. The table is terminated
 *	by an entry specअगरying mask 0.  Returns the number of fatal पूर्णांकerrupt
 *	conditions.
 */
पूर्णांक
csio_handle_पूर्णांकr_status(काष्ठा csio_hw *hw, अचिन्हित पूर्णांक reg,
				 स्थिर काष्ठा पूर्णांकr_info *acts)
अणु
	पूर्णांक fatal = 0;
	अचिन्हित पूर्णांक mask = 0;
	अचिन्हित पूर्णांक status = csio_rd_reg32(hw, reg);

	क्रम ( ; acts->mask; ++acts) अणु
		अगर (!(status & acts->mask))
			जारी;
		अगर (acts->fatal) अणु
			fatal++;
			csio_fatal(hw, "Fatal %s (0x%x)\n",
				    acts->msg, status & acts->mask);
		पूर्ण अन्यथा अगर (acts->msg)
			csio_info(hw, "%s (0x%x)\n",
				    acts->msg, status & acts->mask);
		mask |= acts->mask;
	पूर्ण
	status &= mask;
	अगर (status)                           /* clear processed पूर्णांकerrupts */
		csio_wr_reg32(hw, status, reg);
	वापस fatal;
पूर्ण

/*
 * TP पूर्णांकerrupt handler.
 */
अटल व्योम csio_tp_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info tp_पूर्णांकr_info[] = अणु
		अणु 0x3fffffff, "TP parity error", -1, 1 पूर्ण,
		अणु FLMTXFLSTEMPTY_F, "TP out of Tx pages", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, TP_INT_CAUSE_A, tp_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * SGE पूर्णांकerrupt handler.
 */
अटल व्योम csio_sge_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक64_t v;

	अटल काष्ठा पूर्णांकr_info sge_पूर्णांकr_info[] = अणु
		अणु ERR_CPL_EXCEED_IQE_SIZE_F,
		  "SGE received CPL exceeding IQE size", -1, 1 पूर्ण,
		अणु ERR_INVALID_CIDX_INC_F,
		  "SGE GTS CIDX increment too large", -1, 0 पूर्ण,
		अणु ERR_CPL_OPCODE_0_F, "SGE received 0-length CPL", -1, 0 पूर्ण,
		अणु ERR_DROPPED_DB_F, "SGE doorbell dropped", -1, 0 पूर्ण,
		अणु ERR_DATA_CPL_ON_HIGH_QID1_F | ERR_DATA_CPL_ON_HIGH_QID0_F,
		  "SGE IQID > 1023 received CPL for FL", -1, 0 पूर्ण,
		अणु ERR_BAD_DB_PIDX3_F, "SGE DBP 3 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX2_F, "SGE DBP 2 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX1_F, "SGE DBP 1 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_BAD_DB_PIDX0_F, "SGE DBP 0 pidx increment too large", -1,
		  0 पूर्ण,
		अणु ERR_ING_CTXT_PRIO_F,
		  "SGE too many priority ingress contexts", -1, 0 पूर्ण,
		अणु ERR_EGR_CTXT_PRIO_F,
		  "SGE too many priority egress contexts", -1, 0 पूर्ण,
		अणु INGRESS_SIZE_ERR_F, "SGE illegal ingress QID", -1, 0 पूर्ण,
		अणु EGRESS_SIZE_ERR_F, "SGE illegal egress QID", -1, 0 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	v = (uपूर्णांक64_t)csio_rd_reg32(hw, SGE_INT_CAUSE1_A) |
	    ((uपूर्णांक64_t)csio_rd_reg32(hw, SGE_INT_CAUSE2_A) << 32);
	अगर (v) अणु
		csio_fatal(hw, "SGE parity error (%#llx)\n",
			    (अचिन्हित दीर्घ दीर्घ)v);
		csio_wr_reg32(hw, (uपूर्णांक32_t)(v & 0xFFFFFFFF),
						SGE_INT_CAUSE1_A);
		csio_wr_reg32(hw, (uपूर्णांक32_t)(v >> 32), SGE_INT_CAUSE2_A);
	पूर्ण

	v |= csio_handle_पूर्णांकr_status(hw, SGE_INT_CAUSE3_A, sge_पूर्णांकr_info);

	अगर (csio_handle_पूर्णांकr_status(hw, SGE_INT_CAUSE3_A, sge_पूर्णांकr_info) ||
	    v != 0)
		csio_hw_fatal_err(hw);
पूर्ण

#घोषणा CIM_OBQ_INTR (OBQULP0PARERR_F | OBQULP1PARERR_F | OBQULP2PARERR_F |\
		      OBQULP3PARERR_F | OBQSGEPARERR_F | OBQNCSIPARERR_F)
#घोषणा CIM_IBQ_INTR (IBQTP0PARERR_F | IBQTP1PARERR_F | IBQULPPARERR_F |\
		      IBQSGEHIPARERR_F | IBQSGELOPARERR_F | IBQNCSIPARERR_F)

/*
 * CIM पूर्णांकerrupt handler.
 */
अटल व्योम csio_cim_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info cim_पूर्णांकr_info[] = अणु
		अणु PREFDROPINT_F, "CIM control register prefetch drop", -1, 1 पूर्ण,
		अणु CIM_OBQ_INTR, "CIM OBQ parity error", -1, 1 पूर्ण,
		अणु CIM_IBQ_INTR, "CIM IBQ parity error", -1, 1 पूर्ण,
		अणु MBUPPARERR_F, "CIM mailbox uP parity error", -1, 1 पूर्ण,
		अणु MBHOSTPARERR_F, "CIM mailbox host parity error", -1, 1 पूर्ण,
		अणु TIEQINPARERRINT_F, "CIM TIEQ outgoing parity error", -1, 1 पूर्ण,
		अणु TIEQOUTPARERRINT_F, "CIM TIEQ incoming parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info cim_upपूर्णांकr_info[] = अणु
		अणु RSVDSPACEINT_F, "CIM reserved space access", -1, 1 पूर्ण,
		अणु ILLTRANSINT_F, "CIM illegal transaction", -1, 1 पूर्ण,
		अणु ILLWRINT_F, "CIM illegal write", -1, 1 पूर्ण,
		अणु ILLRDINT_F, "CIM illegal read", -1, 1 पूर्ण,
		अणु ILLRDBEINT_F, "CIM illegal read BE", -1, 1 पूर्ण,
		अणु ILLWRBEINT_F, "CIM illegal write BE", -1, 1 पूर्ण,
		अणु SGLRDBOOTINT_F, "CIM single read from boot space", -1, 1 पूर्ण,
		अणु SGLWRBOOTINT_F, "CIM single write to boot space", -1, 1 पूर्ण,
		अणु BLKWRBOOTINT_F, "CIM block write to boot space", -1, 1 पूर्ण,
		अणु SGLRDFLASHINT_F, "CIM single read from flash space", -1, 1 पूर्ण,
		अणु SGLWRFLASHINT_F, "CIM single write to flash space", -1, 1 पूर्ण,
		अणु BLKWRFLASHINT_F, "CIM block write to flash space", -1, 1 पूर्ण,
		अणु SGLRDEEPROMINT_F, "CIM single EEPROM read", -1, 1 पूर्ण,
		अणु SGLWREEPROMINT_F, "CIM single EEPROM write", -1, 1 पूर्ण,
		अणु BLKRDEEPROMINT_F, "CIM block EEPROM read", -1, 1 पूर्ण,
		अणु BLKWREEPROMINT_F, "CIM block EEPROM write", -1, 1 पूर्ण,
		अणु SGLRDCTLINT_F, "CIM single read from CTL space", -1, 1 पूर्ण,
		अणु SGLWRCTLINT_F, "CIM single write to CTL space", -1, 1 पूर्ण,
		अणु BLKRDCTLINT_F, "CIM block read from CTL space", -1, 1 पूर्ण,
		अणु BLKWRCTLINT_F, "CIM block write to CTL space", -1, 1 पूर्ण,
		अणु SGLRDPLINT_F, "CIM single read from PL space", -1, 1 पूर्ण,
		अणु SGLWRPLINT_F, "CIM single write to PL space", -1, 1 पूर्ण,
		अणु BLKRDPLINT_F, "CIM block read from PL space", -1, 1 पूर्ण,
		अणु BLKWRPLINT_F, "CIM block write to PL space", -1, 1 पूर्ण,
		अणु REQOVRLOOKUPINT_F, "CIM request FIFO overwrite", -1, 1 पूर्ण,
		अणु RSPOVRLOOKUPINT_F, "CIM response FIFO overwrite", -1, 1 पूर्ण,
		अणु TIMEOUTINT_F, "CIM PIF timeout", -1, 1 पूर्ण,
		अणु TIMEOUTMAINT_F, "CIM PIF MA timeout", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	पूर्णांक fat;

	fat = csio_handle_पूर्णांकr_status(hw, CIM_HOST_INT_CAUSE_A,
				      cim_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, CIM_HOST_UPACC_INT_CAUSE_A,
				      cim_upपूर्णांकr_info);
	अगर (fat)
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * ULP RX पूर्णांकerrupt handler.
 */
अटल व्योम csio_ulprx_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info ulprx_पूर्णांकr_info[] = अणु
		अणु 0x1800000, "ULPRX context error", -1, 1 पूर्ण,
		अणु 0x7fffff, "ULPRX parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, ULP_RX_INT_CAUSE_A, ulprx_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * ULP TX पूर्णांकerrupt handler.
 */
अटल व्योम csio_ulptx_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info ulptx_पूर्णांकr_info[] = अणु
		अणु PBL_BOUND_ERR_CH3_F, "ULPTX channel 3 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH2_F, "ULPTX channel 2 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH1_F, "ULPTX channel 1 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु PBL_BOUND_ERR_CH0_F, "ULPTX channel 0 PBL out of bounds", -1,
		  0 पूर्ण,
		अणु 0xfffffff, "ULPTX parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, ULP_TX_INT_CAUSE_A, ulptx_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * PM TX पूर्णांकerrupt handler.
 */
अटल व्योम csio_pmtx_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info pmtx_पूर्णांकr_info[] = अणु
		अणु PCMD_LEN_OVFL0_F, "PMTX channel 0 pcmd too large", -1, 1 पूर्ण,
		अणु PCMD_LEN_OVFL1_F, "PMTX channel 1 pcmd too large", -1, 1 पूर्ण,
		अणु PCMD_LEN_OVFL2_F, "PMTX channel 2 pcmd too large", -1, 1 पूर्ण,
		अणु ZERO_C_CMD_ERROR_F, "PMTX 0-length pcmd", -1, 1 पूर्ण,
		अणु 0xffffff0, "PMTX framing error", -1, 1 पूर्ण,
		अणु OESPI_PAR_ERROR_F, "PMTX oespi parity error", -1, 1 पूर्ण,
		अणु DB_OPTIONS_PAR_ERROR_F, "PMTX db_options parity error", -1,
		  1 पूर्ण,
		अणु ICSPI_PAR_ERROR_F, "PMTX icspi parity error", -1, 1 पूर्ण,
		अणु PMTX_C_PCMD_PAR_ERROR_F, "PMTX c_pcmd parity error", -1, 1पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, PM_TX_INT_CAUSE_A, pmtx_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * PM RX पूर्णांकerrupt handler.
 */
अटल व्योम csio_pmrx_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info pmrx_पूर्णांकr_info[] = अणु
		अणु ZERO_E_CMD_ERROR_F, "PMRX 0-length pcmd", -1, 1 पूर्ण,
		अणु 0x3ffff0, "PMRX framing error", -1, 1 पूर्ण,
		अणु OCSPI_PAR_ERROR_F, "PMRX ocspi parity error", -1, 1 पूर्ण,
		अणु DB_OPTIONS_PAR_ERROR_F, "PMRX db_options parity error", -1,
		  1 पूर्ण,
		अणु IESPI_PAR_ERROR_F, "PMRX iespi parity error", -1, 1 पूर्ण,
		अणु PMRX_E_PCMD_PAR_ERROR_F, "PMRX e_pcmd parity error", -1, 1पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, PM_RX_INT_CAUSE_A, pmrx_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * CPL चयन पूर्णांकerrupt handler.
 */
अटल व्योम csio_cplsw_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info cplsw_पूर्णांकr_info[] = अणु
		अणु CIM_OP_MAP_PERR_F, "CPLSW CIM op_map parity error", -1, 1 पूर्ण,
		अणु CIM_OVFL_ERROR_F, "CPLSW CIM overflow", -1, 1 पूर्ण,
		अणु TP_FRAMING_ERROR_F, "CPLSW TP framing error", -1, 1 पूर्ण,
		अणु SGE_FRAMING_ERROR_F, "CPLSW SGE framing error", -1, 1 पूर्ण,
		अणु CIM_FRAMING_ERROR_F, "CPLSW CIM framing error", -1, 1 पूर्ण,
		अणु ZERO_SWITCH_ERROR_F, "CPLSW no-switch error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, CPL_INTR_CAUSE_A, cplsw_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * LE पूर्णांकerrupt handler.
 */
अटल व्योम csio_le_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	क्रमागत chip_type chip = CHELSIO_CHIP_VERSION(hw->chip_id);

	अटल काष्ठा पूर्णांकr_info le_पूर्णांकr_info[] = अणु
		अणु LIPMISS_F, "LE LIP miss", -1, 0 पूर्ण,
		अणु LIP0_F, "LE 0 LIP error", -1, 0 पूर्ण,
		अणु PARITYERR_F, "LE parity error", -1, 1 पूर्ण,
		अणु UNKNOWNCMD_F, "LE unknown command", -1, 1 पूर्ण,
		अणु REQQPARERR_F, "LE request queue parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अटल काष्ठा पूर्णांकr_info t6_le_पूर्णांकr_info[] = अणु
		अणु T6_LIPMISS_F, "LE LIP miss", -1, 0 पूर्ण,
		अणु T6_LIP0_F, "LE 0 LIP error", -1, 0 पूर्ण,
		अणु TCAMINTPERR_F, "LE parity error", -1, 1 पूर्ण,
		अणु T6_UNKNOWNCMD_F, "LE unknown command", -1, 1 पूर्ण,
		अणु SSRAMINTPERR_F, "LE request queue parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, LE_DB_INT_CAUSE_A,
				    (chip == CHELSIO_T5) ?
				    le_पूर्णांकr_info : t6_le_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * MPS पूर्णांकerrupt handler.
 */
अटल व्योम csio_mps_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info mps_rx_पूर्णांकr_info[] = अणु
		अणु 0xffffff, "MPS Rx parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_tx_पूर्णांकr_info[] = अणु
		अणु TPFIFO_V(TPFIFO_M), "MPS Tx TP FIFO parity error", -1, 1 पूर्ण,
		अणु NCSIFIFO_F, "MPS Tx NC-SI FIFO parity error", -1, 1 पूर्ण,
		अणु TXDATAFIFO_V(TXDATAFIFO_M), "MPS Tx data FIFO parity error",
		  -1, 1 पूर्ण,
		अणु TXDESCFIFO_V(TXDESCFIFO_M), "MPS Tx desc FIFO parity error",
		  -1, 1 पूर्ण,
		अणु BUBBLE_F, "MPS Tx underflow", -1, 1 पूर्ण,
		अणु SECNTERR_F, "MPS Tx SOP/EOP error", -1, 1 पूर्ण,
		अणु FRMERR_F, "MPS Tx framing error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_trc_पूर्णांकr_info[] = अणु
		अणु FILTMEM_V(FILTMEM_M), "MPS TRC filter parity error", -1, 1 पूर्ण,
		अणु PKTFIFO_V(PKTFIFO_M), "MPS TRC packet FIFO parity error",
		  -1, 1 पूर्ण,
		अणु MISCPERR_F, "MPS TRC misc parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_stat_sram_पूर्णांकr_info[] = अणु
		अणु 0x1fffff, "MPS statistics SRAM parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_stat_tx_पूर्णांकr_info[] = अणु
		अणु 0xfffff, "MPS statistics Tx FIFO parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_stat_rx_पूर्णांकr_info[] = अणु
		अणु 0xffffff, "MPS statistics Rx FIFO parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;
	अटल काष्ठा पूर्णांकr_info mps_cls_पूर्णांकr_info[] = अणु
		अणु MATCHSRAM_F, "MPS match SRAM parity error", -1, 1 पूर्ण,
		अणु MATCHTCAM_F, "MPS match TCAM parity error", -1, 1 पूर्ण,
		अणु HASHSRAM_F, "MPS hash SRAM parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	पूर्णांक fat;

	fat = csio_handle_पूर्णांकr_status(hw, MPS_RX_PERR_INT_CAUSE_A,
				      mps_rx_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_TX_INT_CAUSE_A,
				      mps_tx_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_TRC_INT_CAUSE_A,
				      mps_trc_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_STAT_PERR_INT_CAUSE_SRAM_A,
				      mps_stat_sram_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_STAT_PERR_INT_CAUSE_TX_FIFO_A,
				      mps_stat_tx_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_STAT_PERR_INT_CAUSE_RX_FIFO_A,
				      mps_stat_rx_पूर्णांकr_info) +
	      csio_handle_पूर्णांकr_status(hw, MPS_CLS_INT_CAUSE_A,
				      mps_cls_पूर्णांकr_info);

	csio_wr_reg32(hw, 0, MPS_INT_CAUSE_A);
	csio_rd_reg32(hw, MPS_INT_CAUSE_A);                    /* flush */
	अगर (fat)
		csio_hw_fatal_err(hw);
पूर्ण

#घोषणा MEM_INT_MASK (PERR_INT_CAUSE_F | ECC_CE_INT_CAUSE_F | \
		      ECC_UE_INT_CAUSE_F)

/*
 * EDC/MC पूर्णांकerrupt handler.
 */
अटल व्योम csio_mem_पूर्णांकr_handler(काष्ठा csio_hw *hw, पूर्णांक idx)
अणु
	अटल स्थिर अक्षर name[3][5] = अणु "EDC0", "EDC1", "MC" पूर्ण;

	अचिन्हित पूर्णांक addr, cnt_addr, v;

	अगर (idx <= MEM_EDC1) अणु
		addr = EDC_REG(EDC_INT_CAUSE_A, idx);
		cnt_addr = EDC_REG(EDC_ECC_STATUS_A, idx);
	पूर्ण अन्यथा अणु
		addr = MC_INT_CAUSE_A;
		cnt_addr = MC_ECC_STATUS_A;
	पूर्ण

	v = csio_rd_reg32(hw, addr) & MEM_INT_MASK;
	अगर (v & PERR_INT_CAUSE_F)
		csio_fatal(hw, "%s FIFO parity error\n", name[idx]);
	अगर (v & ECC_CE_INT_CAUSE_F) अणु
		uपूर्णांक32_t cnt = ECC_CECNT_G(csio_rd_reg32(hw, cnt_addr));

		csio_wr_reg32(hw, ECC_CECNT_V(ECC_CECNT_M), cnt_addr);
		csio_warn(hw, "%u %s correctable ECC data error%s\n",
			    cnt, name[idx], cnt > 1 ? "s" : "");
	पूर्ण
	अगर (v & ECC_UE_INT_CAUSE_F)
		csio_fatal(hw, "%s uncorrectable ECC data error\n", name[idx]);

	csio_wr_reg32(hw, v, addr);
	अगर (v & (PERR_INT_CAUSE_F | ECC_UE_INT_CAUSE_F))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * MA पूर्णांकerrupt handler.
 */
अटल व्योम csio_ma_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक32_t v, status = csio_rd_reg32(hw, MA_INT_CAUSE_A);

	अगर (status & MEM_PERR_INT_CAUSE_F)
		csio_fatal(hw, "MA parity error, parity status %#x\n",
			    csio_rd_reg32(hw, MA_PARITY_ERROR_STATUS_A));
	अगर (status & MEM_WRAP_INT_CAUSE_F) अणु
		v = csio_rd_reg32(hw, MA_INT_WRAP_STATUS_A);
		csio_fatal(hw,
		   "MA address wrap-around error by client %u to address %#x\n",
		   MEM_WRAP_CLIENT_NUM_G(v), MEM_WRAP_ADDRESS_G(v) << 4);
	पूर्ण
	csio_wr_reg32(hw, status, MA_INT_CAUSE_A);
	csio_hw_fatal_err(hw);
पूर्ण

/*
 * SMB पूर्णांकerrupt handler.
 */
अटल व्योम csio_smb_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info smb_पूर्णांकr_info[] = अणु
		अणु MSTTXFIFOPARINT_F, "SMB master Tx FIFO parity error", -1, 1 पूर्ण,
		अणु MSTRXFIFOPARINT_F, "SMB master Rx FIFO parity error", -1, 1 पूर्ण,
		अणु SLVFIFOPARINT_F, "SMB slave FIFO parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, SMB_INT_CAUSE_A, smb_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * NC-SI पूर्णांकerrupt handler.
 */
अटल व्योम csio_ncsi_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info ncsi_पूर्णांकr_info[] = अणु
		अणु CIM_DM_PRTY_ERR_F, "NC-SI CIM parity error", -1, 1 पूर्ण,
		अणु MPS_DM_PRTY_ERR_F, "NC-SI MPS parity error", -1, 1 पूर्ण,
		अणु TXFIFO_PRTY_ERR_F, "NC-SI Tx FIFO parity error", -1, 1 पूर्ण,
		अणु RXFIFO_PRTY_ERR_F, "NC-SI Rx FIFO parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, NCSI_INT_CAUSE_A, ncsi_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 * XGMAC पूर्णांकerrupt handler.
 */
अटल व्योम csio_xgmac_पूर्णांकr_handler(काष्ठा csio_hw *hw, पूर्णांक port)
अणु
	uपूर्णांक32_t v = csio_rd_reg32(hw, T5_PORT_REG(port, MAC_PORT_INT_CAUSE_A));

	v &= TXFIFO_PRTY_ERR_F | RXFIFO_PRTY_ERR_F;
	अगर (!v)
		वापस;

	अगर (v & TXFIFO_PRTY_ERR_F)
		csio_fatal(hw, "XGMAC %d Tx FIFO parity error\n", port);
	अगर (v & RXFIFO_PRTY_ERR_F)
		csio_fatal(hw, "XGMAC %d Rx FIFO parity error\n", port);
	csio_wr_reg32(hw, v, T5_PORT_REG(port, MAC_PORT_INT_CAUSE_A));
	csio_hw_fatal_err(hw);
पूर्ण

/*
 * PL पूर्णांकerrupt handler.
 */
अटल व्योम csio_pl_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	अटल काष्ठा पूर्णांकr_info pl_पूर्णांकr_info[] = अणु
		अणु FATALPERR_F, "T4 fatal parity error", -1, 1 पूर्ण,
		अणु PERRVFID_F, "PL VFID_MAP parity error", -1, 1 पूर्ण,
		अणु 0, शून्य, 0, 0 पूर्ण
	पूर्ण;

	अगर (csio_handle_पूर्णांकr_status(hw, PL_PL_INT_CAUSE_A, pl_पूर्णांकr_info))
		csio_hw_fatal_err(hw);
पूर्ण

/*
 *	csio_hw_slow_पूर्णांकr_handler - control path पूर्णांकerrupt handler
 *	@hw: HW module
 *
 *	Interrupt handler क्रम non-data global पूर्णांकerrupt events, e.g., errors.
 *	The designation 'slow' is because it involves रेजिस्टर पढ़ोs, जबतक
 *	data पूर्णांकerrupts typically करोn't involve any MMIOs.
 */
पूर्णांक
csio_hw_slow_पूर्णांकr_handler(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक32_t cause = csio_rd_reg32(hw, PL_INT_CAUSE_A);

	अगर (!(cause & CSIO_GLBL_INTR_MASK)) अणु
		CSIO_INC_STATS(hw, n_plपूर्णांक_unexp);
		वापस 0;
	पूर्ण

	csio_dbg(hw, "Slow interrupt! cause: 0x%x\n", cause);

	CSIO_INC_STATS(hw, n_plपूर्णांक_cnt);

	अगर (cause & CIM_F)
		csio_cim_पूर्णांकr_handler(hw);

	अगर (cause & MPS_F)
		csio_mps_पूर्णांकr_handler(hw);

	अगर (cause & NCSI_F)
		csio_ncsi_पूर्णांकr_handler(hw);

	अगर (cause & PL_F)
		csio_pl_पूर्णांकr_handler(hw);

	अगर (cause & SMB_F)
		csio_smb_पूर्णांकr_handler(hw);

	अगर (cause & XGMAC0_F)
		csio_xgmac_पूर्णांकr_handler(hw, 0);

	अगर (cause & XGMAC1_F)
		csio_xgmac_पूर्णांकr_handler(hw, 1);

	अगर (cause & XGMAC_KR0_F)
		csio_xgmac_पूर्णांकr_handler(hw, 2);

	अगर (cause & XGMAC_KR1_F)
		csio_xgmac_पूर्णांकr_handler(hw, 3);

	अगर (cause & PCIE_F)
		hw->chip_ops->chip_pcie_पूर्णांकr_handler(hw);

	अगर (cause & MC_F)
		csio_mem_पूर्णांकr_handler(hw, MEM_MC);

	अगर (cause & EDC0_F)
		csio_mem_पूर्णांकr_handler(hw, MEM_EDC0);

	अगर (cause & EDC1_F)
		csio_mem_पूर्णांकr_handler(hw, MEM_EDC1);

	अगर (cause & LE_F)
		csio_le_पूर्णांकr_handler(hw);

	अगर (cause & TP_F)
		csio_tp_पूर्णांकr_handler(hw);

	अगर (cause & MA_F)
		csio_ma_पूर्णांकr_handler(hw);

	अगर (cause & PM_TX_F)
		csio_pmtx_पूर्णांकr_handler(hw);

	अगर (cause & PM_RX_F)
		csio_pmrx_पूर्णांकr_handler(hw);

	अगर (cause & ULP_RX_F)
		csio_ulprx_पूर्णांकr_handler(hw);

	अगर (cause & CPL_SWITCH_F)
		csio_cplsw_पूर्णांकr_handler(hw);

	अगर (cause & SGE_F)
		csio_sge_पूर्णांकr_handler(hw);

	अगर (cause & ULP_TX_F)
		csio_ulptx_पूर्णांकr_handler(hw);

	/* Clear the पूर्णांकerrupts just processed क्रम which we are the master. */
	csio_wr_reg32(hw, cause & CSIO_GLBL_INTR_MASK, PL_INT_CAUSE_A);
	csio_rd_reg32(hw, PL_INT_CAUSE_A); /* flush */

	वापस 1;
पूर्ण

/*****************************************************************************
 * HW <--> mailbox पूर्णांकerfacing routines.
 ****************************************************************************/
/*
 * csio_mberr_worker - Worker thपढ़ो (dpc) क्रम mailbox/error completions
 *
 * @data: Private data poपूर्णांकer.
 *
 * Called from worker thपढ़ो context.
 */
अटल व्योम
csio_mberr_worker(व्योम *data)
अणु
	काष्ठा csio_hw *hw = (काष्ठा csio_hw *)data;
	काष्ठा csio_mbm *mbm = &hw->mbm;
	LIST_HEAD(cbfn_q);
	काष्ठा csio_mb *mbp_next;
	पूर्णांक rv;

	del_समयr_sync(&mbm->समयr);

	spin_lock_irq(&hw->lock);
	अगर (list_empty(&mbm->cbfn_q)) अणु
		spin_unlock_irq(&hw->lock);
		वापस;
	पूर्ण

	list_splice_tail_init(&mbm->cbfn_q, &cbfn_q);
	mbm->stats.n_cbfnq = 0;

	/* Try to start रुकोing mailboxes */
	अगर (!list_empty(&mbm->req_q)) अणु
		mbp_next = list_first_entry(&mbm->req_q, काष्ठा csio_mb, list);
		list_del_init(&mbp_next->list);

		rv = csio_mb_issue(hw, mbp_next);
		अगर (rv != 0)
			list_add_tail(&mbp_next->list, &mbm->req_q);
		अन्यथा
			CSIO_DEC_STATS(mbm, n_activeq);
	पूर्ण
	spin_unlock_irq(&hw->lock);

	/* Now callback completions */
	csio_mb_completions(hw, &cbfn_q);
पूर्ण

/*
 * csio_hw_mb_समयr - Top-level Mailbox समयout handler.
 *
 * @data: निजी data poपूर्णांकer
 *
 **/
अटल व्योम
csio_hw_mb_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा csio_mbm *mbm = from_समयr(mbm, t, समयr);
	काष्ठा csio_hw *hw = mbm->hw;
	काष्ठा csio_mb *mbp = शून्य;

	spin_lock_irq(&hw->lock);
	mbp = csio_mb_पंचांगo_handler(hw);
	spin_unlock_irq(&hw->lock);

	/* Call back the function क्रम the समयd-out Mailbox */
	अगर (mbp)
		mbp->mb_cbfn(hw, mbp);

पूर्ण

/*
 * csio_hw_mbm_cleanup - Cleanup Mailbox module.
 * @hw: HW module
 *
 * Called with lock held, should निकास with lock held.
 * Cancels outstanding mailboxes (रुकोing, in-flight) and gathers them
 * पूर्णांकo a local queue. Drops lock and calls the completions. Holds
 * lock and वापसs.
 */
अटल व्योम
csio_hw_mbm_cleanup(काष्ठा csio_hw *hw)
अणु
	LIST_HEAD(cbfn_q);

	csio_mb_cancel_all(hw, &cbfn_q);

	spin_unlock_irq(&hw->lock);
	csio_mb_completions(hw, &cbfn_q);
	spin_lock_irq(&hw->lock);
पूर्ण

/*****************************************************************************
 * Event handling
 ****************************************************************************/
पूर्णांक
csio_enqueue_evt(काष्ठा csio_hw *hw, क्रमागत csio_evt type, व्योम *evt_msg,
			uपूर्णांक16_t len)
अणु
	काष्ठा csio_evt_msg *evt_entry = शून्य;

	अगर (type >= CSIO_EVT_MAX)
		वापस -EINVAL;

	अगर (len > CSIO_EVT_MSG_SIZE)
		वापस -EINVAL;

	अगर (hw->flags & CSIO_HWF_FWEVT_STOP)
		वापस -EINVAL;

	अगर (list_empty(&hw->evt_मुक्त_q)) अणु
		csio_err(hw, "Failed to alloc evt entry, msg type %d len %d\n",
			 type, len);
		वापस -ENOMEM;
	पूर्ण

	evt_entry = list_first_entry(&hw->evt_मुक्त_q,
				     काष्ठा csio_evt_msg, list);
	list_del_init(&evt_entry->list);

	/* copy event msg and queue the event */
	evt_entry->type = type;
	स_नकल((व्योम *)evt_entry->data, evt_msg, len);
	list_add_tail(&evt_entry->list, &hw->evt_active_q);

	CSIO_DEC_STATS(hw, n_evt_मुक्तq);
	CSIO_INC_STATS(hw, n_evt_activeq);

	वापस 0;
पूर्ण

अटल पूर्णांक
csio_enqueue_evt_lock(काष्ठा csio_hw *hw, क्रमागत csio_evt type, व्योम *evt_msg,
			uपूर्णांक16_t len, bool msg_sg)
अणु
	काष्ठा csio_evt_msg *evt_entry = शून्य;
	काष्ठा csio_fl_dma_buf *fl_sg;
	uपूर्णांक32_t off = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक n, ret = 0;

	अगर (type >= CSIO_EVT_MAX)
		वापस -EINVAL;

	अगर (len > CSIO_EVT_MSG_SIZE)
		वापस -EINVAL;

	spin_lock_irqsave(&hw->lock, flags);
	अगर (hw->flags & CSIO_HWF_FWEVT_STOP) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (list_empty(&hw->evt_मुक्त_q)) अणु
		csio_err(hw, "Failed to alloc evt entry, msg type %d len %d\n",
			 type, len);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	evt_entry = list_first_entry(&hw->evt_मुक्त_q,
				     काष्ठा csio_evt_msg, list);
	list_del_init(&evt_entry->list);

	/* copy event msg and queue the event */
	evt_entry->type = type;

	/* If Payload in SG list*/
	अगर (msg_sg) अणु
		fl_sg = (काष्ठा csio_fl_dma_buf *) evt_msg;
		क्रम (n = 0; (n < CSIO_MAX_FLBUF_PER_IQWR && off < len); n++) अणु
			स_नकल((व्योम *)((uपूर्णांकptr_t)evt_entry->data + off),
				fl_sg->flbufs[n].vaddr,
				fl_sg->flbufs[n].len);
			off += fl_sg->flbufs[n].len;
		पूर्ण
	पूर्ण अन्यथा
		स_नकल((व्योम *)evt_entry->data, evt_msg, len);

	list_add_tail(&evt_entry->list, &hw->evt_active_q);
	CSIO_DEC_STATS(hw, n_evt_मुक्तq);
	CSIO_INC_STATS(hw, n_evt_activeq);
out:
	spin_unlock_irqrestore(&hw->lock, flags);
	वापस ret;
पूर्ण

अटल व्योम
csio_मुक्त_evt(काष्ठा csio_hw *hw, काष्ठा csio_evt_msg *evt_entry)
अणु
	अगर (evt_entry) अणु
		spin_lock_irq(&hw->lock);
		list_del_init(&evt_entry->list);
		list_add_tail(&evt_entry->list, &hw->evt_मुक्त_q);
		CSIO_DEC_STATS(hw, n_evt_activeq);
		CSIO_INC_STATS(hw, n_evt_मुक्तq);
		spin_unlock_irq(&hw->lock);
	पूर्ण
पूर्ण

व्योम
csio_evtq_flush(काष्ठा csio_hw *hw)
अणु
	uपूर्णांक32_t count;
	count = 30;
	जबतक (hw->flags & CSIO_HWF_FWEVT_PENDING && count--) अणु
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	पूर्ण

	CSIO_DB_ASSERT(!(hw->flags & CSIO_HWF_FWEVT_PENDING));
पूर्ण

अटल व्योम
csio_evtq_stop(काष्ठा csio_hw *hw)
अणु
	hw->flags |= CSIO_HWF_FWEVT_STOP;
पूर्ण

अटल व्योम
csio_evtq_start(काष्ठा csio_hw *hw)
अणु
	hw->flags &= ~CSIO_HWF_FWEVT_STOP;
पूर्ण

अटल व्योम
csio_evtq_cleanup(काष्ठा csio_hw *hw)
अणु
	काष्ठा list_head *evt_entry, *next_entry;

	/* Release outstanding events from activeq to मुक्तq*/
	अगर (!list_empty(&hw->evt_active_q))
		list_splice_tail_init(&hw->evt_active_q, &hw->evt_मुक्त_q);

	hw->stats.n_evt_activeq = 0;
	hw->flags &= ~CSIO_HWF_FWEVT_PENDING;

	/* Freeup event entry */
	list_क्रम_each_safe(evt_entry, next_entry, &hw->evt_मुक्त_q) अणु
		kमुक्त(evt_entry);
		CSIO_DEC_STATS(hw, n_evt_मुक्तq);
	पूर्ण

	hw->stats.n_evt_मुक्तq = 0;
पूर्ण


अटल व्योम
csio_process_fwevtq_entry(काष्ठा csio_hw *hw, व्योम *wr, uपूर्णांक32_t len,
			  काष्ठा csio_fl_dma_buf *flb, व्योम *priv)
अणु
	__u8 op;
	व्योम *msg = शून्य;
	uपूर्णांक32_t msg_len = 0;
	bool msg_sg = 0;

	op = ((काष्ठा rss_header *) wr)->opcode;
	अगर (op == CPL_FW6_PLD) अणु
		CSIO_INC_STATS(hw, n_cpl_fw6_pld);
		अगर (!flb || !flb->totlen) अणु
			CSIO_INC_STATS(hw, n_cpl_unexp);
			वापस;
		पूर्ण

		msg = (व्योम *) flb;
		msg_len = flb->totlen;
		msg_sg = 1;
	पूर्ण अन्यथा अगर (op == CPL_FW6_MSG || op == CPL_FW4_MSG) अणु

		CSIO_INC_STATS(hw, n_cpl_fw6_msg);
		/* skip RSS header */
		msg = (व्योम *)((uपूर्णांकptr_t)wr + माप(__be64));
		msg_len = (op == CPL_FW6_MSG) ? माप(काष्ठा cpl_fw6_msg) :
			   माप(काष्ठा cpl_fw4_msg);
	पूर्ण अन्यथा अणु
		csio_warn(hw, "unexpected CPL %#x on FW event queue\n", op);
		CSIO_INC_STATS(hw, n_cpl_unexp);
		वापस;
	पूर्ण

	/*
	 * Enqueue event to EventQ. Events processing happens
	 * in Event worker thपढ़ो context
	 */
	अगर (csio_enqueue_evt_lock(hw, CSIO_EVT_FW, msg,
				  (uपूर्णांक16_t)msg_len, msg_sg))
		CSIO_INC_STATS(hw, n_evt_drop);
पूर्ण

व्योम
csio_evtq_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा csio_hw *hw = container_of(work, काष्ठा csio_hw, evtq_work);
	काष्ठा list_head *evt_entry, *next_entry;
	LIST_HEAD(evt_q);
	काष्ठा csio_evt_msg	*evt_msg;
	काष्ठा cpl_fw6_msg *msg;
	काष्ठा csio_rnode *rn;
	पूर्णांक rv = 0;
	uपूर्णांक8_t evtq_stop = 0;

	csio_dbg(hw, "event worker thread active evts#%d\n",
		 hw->stats.n_evt_activeq);

	spin_lock_irq(&hw->lock);
	जबतक (!list_empty(&hw->evt_active_q)) अणु
		list_splice_tail_init(&hw->evt_active_q, &evt_q);
		spin_unlock_irq(&hw->lock);

		list_क्रम_each_safe(evt_entry, next_entry, &evt_q) अणु
			evt_msg = (काष्ठा csio_evt_msg *) evt_entry;

			/* Drop events अगर queue is STOPPED */
			spin_lock_irq(&hw->lock);
			अगर (hw->flags & CSIO_HWF_FWEVT_STOP)
				evtq_stop = 1;
			spin_unlock_irq(&hw->lock);
			अगर (evtq_stop) अणु
				CSIO_INC_STATS(hw, n_evt_drop);
				जाओ मुक्त_evt;
			पूर्ण

			चयन (evt_msg->type) अणु
			हाल CSIO_EVT_FW:
				msg = (काष्ठा cpl_fw6_msg *)(evt_msg->data);

				अगर ((msg->opcode == CPL_FW6_MSG ||
				     msg->opcode == CPL_FW4_MSG) &&
				    !msg->type) अणु
					rv = csio_mb_fwevt_handler(hw,
								msg->data);
					अगर (!rv)
						अवरोध;
					/* Handle any reमुख्यing fw events */
					csio_fcoe_fwevt_handler(hw,
							msg->opcode, msg->data);
				पूर्ण अन्यथा अगर (msg->opcode == CPL_FW6_PLD) अणु

					csio_fcoe_fwevt_handler(hw,
							msg->opcode, msg->data);
				पूर्ण अन्यथा अणु
					csio_warn(hw,
					     "Unhandled FW msg op %x type %x\n",
						  msg->opcode, msg->type);
					CSIO_INC_STATS(hw, n_evt_drop);
				पूर्ण
				अवरोध;

			हाल CSIO_EVT_MBX:
				csio_mberr_worker(hw);
				अवरोध;

			हाल CSIO_EVT_DEV_LOSS:
				स_नकल(&rn, evt_msg->data, माप(rn));
				csio_rnode_devloss_handler(rn);
				अवरोध;

			शेष:
				csio_warn(hw, "Unhandled event %x on evtq\n",
					  evt_msg->type);
				CSIO_INC_STATS(hw, n_evt_unexp);
				अवरोध;
			पूर्ण
मुक्त_evt:
			csio_मुक्त_evt(hw, evt_msg);
		पूर्ण

		spin_lock_irq(&hw->lock);
	पूर्ण
	hw->flags &= ~CSIO_HWF_FWEVT_PENDING;
	spin_unlock_irq(&hw->lock);
पूर्ण

पूर्णांक
csio_fwevtq_handler(काष्ठा csio_hw *hw)
अणु
	पूर्णांक rv;

	अगर (csio_q_iqid(hw, hw->fwevt_iq_idx) == CSIO_MAX_QID) अणु
		CSIO_INC_STATS(hw, n_पूर्णांक_stray);
		वापस -EINVAL;
	पूर्ण

	rv = csio_wr_process_iq_idx(hw, hw->fwevt_iq_idx,
			   csio_process_fwevtq_entry, शून्य);
	वापस rv;
पूर्ण

/****************************************************************************
 * Entry poपूर्णांकs
 ****************************************************************************/

/* Management module */
/*
 * csio_mgmt_req_lookup - Lookup the given IO req exist in Active Q.
 * mgmt - mgmt module
 * @io_req - io request
 *
 * Return - 0:अगर given IO Req exists in active Q.
 *          -EINVAL  :अगर lookup fails.
 */
पूर्णांक
csio_mgmt_req_lookup(काष्ठा csio_mgmपंचांग *mgmपंचांग, काष्ठा csio_ioreq *io_req)
अणु
	काष्ठा list_head *पंचांगp;

	/* Lookup ioreq in the ACTIVEQ */
	list_क्रम_each(पंचांगp, &mgmपंचांग->active_q) अणु
		अगर (io_req == (काष्ठा csio_ioreq *)पंचांगp)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा	ECM_MIN_TMO	1000	/* Minimum समयout value क्रम req */

/*
 * csio_mgmts_पंचांगo_handler - MGMT IO Timeout handler.
 * @data - Event data.
 *
 * Return - none.
 */
अटल व्योम
csio_mgmt_पंचांगo_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा csio_mgmपंचांग *mgmपंचांग = from_समयr(mgmपंचांग, t, mgmt_समयr);
	काष्ठा list_head *पंचांगp;
	काष्ठा csio_ioreq *io_req;

	csio_dbg(mgmपंचांग->hw, "Mgmt timer invoked!\n");

	spin_lock_irq(&mgmपंचांग->hw->lock);

	list_क्रम_each(पंचांगp, &mgmपंचांग->active_q) अणु
		io_req = (काष्ठा csio_ioreq *) पंचांगp;
		io_req->पंचांगo -= min_t(uपूर्णांक32_t, io_req->पंचांगo, ECM_MIN_TMO);

		अगर (!io_req->पंचांगo) अणु
			/* Dequeue the request from retry Q. */
			पंचांगp = csio_list_prev(पंचांगp);
			list_del_init(&io_req->sm.sm_list);
			अगर (io_req->io_cbfn) अणु
				/* io_req will be मुक्तd by completion handler */
				io_req->wr_status = -ETIMEDOUT;
				io_req->io_cbfn(mgmपंचांग->hw, io_req);
			पूर्ण अन्यथा अणु
				CSIO_DB_ASSERT(0);
			पूर्ण
		पूर्ण
	पूर्ण

	/* If retry queue is not empty, re-arm समयr */
	अगर (!list_empty(&mgmपंचांग->active_q))
		mod_समयr(&mgmपंचांग->mgmt_समयr,
			  jअगरfies + msecs_to_jअगरfies(ECM_MIN_TMO));
	spin_unlock_irq(&mgmपंचांग->hw->lock);
पूर्ण

अटल व्योम
csio_mgmपंचांग_cleanup(काष्ठा csio_mgmपंचांग *mgmपंचांग)
अणु
	काष्ठा csio_hw *hw = mgmपंचांग->hw;
	काष्ठा csio_ioreq *io_req;
	काष्ठा list_head *पंचांगp;
	uपूर्णांक32_t count;

	count = 30;
	/* Wait क्रम all outstanding req to complete gracefully */
	जबतक ((!list_empty(&mgmपंचांग->active_q)) && count--) अणु
		spin_unlock_irq(&hw->lock);
		msleep(2000);
		spin_lock_irq(&hw->lock);
	पूर्ण

	/* release outstanding req from ACTIVEQ */
	list_क्रम_each(पंचांगp, &mgmपंचांग->active_q) अणु
		io_req = (काष्ठा csio_ioreq *) पंचांगp;
		पंचांगp = csio_list_prev(पंचांगp);
		list_del_init(&io_req->sm.sm_list);
		mgmपंचांग->stats.n_active--;
		अगर (io_req->io_cbfn) अणु
			/* io_req will be मुक्तd by completion handler */
			io_req->wr_status = -ETIMEDOUT;
			io_req->io_cbfn(mgmपंचांग->hw, io_req);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * csio_mgmt_init - Mgmt module init entry poपूर्णांक
 * @mgmtsm - mgmt module
 * @hw	 - HW module
 *
 * Initialize mgmt समयr, resource रुको queue, active queue,
 * completion q. Allocate Egress and Ingress
 * WR queues and save off the queue index वापसed by the WR
 * module क्रम future use. Allocate and save off mgmt reqs in the
 * mgmt_req_मुक्तlist क्रम future use. Make sure their SM is initialized
 * to uninit state.
 * Returns: 0 - on success
 *          -ENOMEM   - on error.
 */
अटल पूर्णांक
csio_mgmपंचांग_init(काष्ठा csio_mgmपंचांग *mgmपंचांग, काष्ठा csio_hw *hw)
अणु
	समयr_setup(&mgmपंचांग->mgmt_समयr, csio_mgmt_पंचांगo_handler, 0);

	INIT_LIST_HEAD(&mgmपंचांग->active_q);
	INIT_LIST_HEAD(&mgmपंचांग->cbfn_q);

	mgmपंचांग->hw = hw;
	/*mgmपंचांग->iq_idx = hw->fwevt_iq_idx;*/

	वापस 0;
पूर्ण

/*
 * csio_mgmपंचांग_निकास - MGMT module निकास entry poपूर्णांक
 * @mgmtsm - mgmt module
 *
 * This function called during MGMT module uninit.
 * Stop समयrs, मुक्त ioreqs allocated.
 * Returns: None
 *
 */
अटल व्योम
csio_mgmपंचांग_निकास(काष्ठा csio_mgmपंचांग *mgmपंचांग)
अणु
	del_समयr_sync(&mgmपंचांग->mgmt_समयr);
पूर्ण


/**
 * csio_hw_start - Kicks off the HW State machine
 * @hw:		Poपूर्णांकer to HW module.
 *
 * It is assumed that the initialization is a synchronous operation.
 * So when we वापस after posting the event, the HW SM should be in
 * the पढ़ोy state, अगर there were no errors during init.
 */
पूर्णांक
csio_hw_start(काष्ठा csio_hw *hw)
अणु
	spin_lock_irq(&hw->lock);
	csio_post_event(&hw->sm, CSIO_HWE_CFG);
	spin_unlock_irq(&hw->lock);

	अगर (csio_is_hw_पढ़ोy(hw))
		वापस 0;
	अन्यथा अगर (csio_match_state(hw, csio_hws_uninit))
		वापस -EINVAL;
	अन्यथा
		वापस -ENODEV;
पूर्ण

पूर्णांक
csio_hw_stop(काष्ठा csio_hw *hw)
अणु
	csio_post_event(&hw->sm, CSIO_HWE_PCI_REMOVE);

	अगर (csio_is_hw_removing(hw))
		वापस 0;
	अन्यथा
		वापस -EINVAL;
पूर्ण

/* Max reset retries */
#घोषणा CSIO_MAX_RESET_RETRIES	3

/**
 * csio_hw_reset - Reset the hardware
 * @hw:		HW module.
 *
 * Caller should hold lock across this function.
 */
पूर्णांक
csio_hw_reset(काष्ठा csio_hw *hw)
अणु
	अगर (!csio_is_hw_master(hw))
		वापस -EPERM;

	अगर (hw->rst_retries >= CSIO_MAX_RESET_RETRIES) अणु
		csio_dbg(hw, "Max hw reset attempts reached..");
		वापस -EINVAL;
	पूर्ण

	hw->rst_retries++;
	csio_post_event(&hw->sm, CSIO_HWE_HBA_RESET);

	अगर (csio_is_hw_पढ़ोy(hw)) अणु
		hw->rst_retries = 0;
		hw->stats.n_reset_start = jअगरfies_to_msecs(jअगरfies);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

/*
 * csio_hw_get_device_id - Caches the Adapter's venकरोr & device id.
 * @hw: HW module.
 */
अटल व्योम
csio_hw_get_device_id(काष्ठा csio_hw *hw)
अणु
	/* Is the adapter device id cached alपढ़ोy ?*/
	अगर (csio_is_dev_id_cached(hw))
		वापस;

	/* Get the PCI venकरोr & device id */
	pci_पढ़ो_config_word(hw->pdev, PCI_VENDOR_ID,
			     &hw->params.pci.venकरोr_id);
	pci_पढ़ो_config_word(hw->pdev, PCI_DEVICE_ID,
			     &hw->params.pci.device_id);

	csio_dev_id_cached(hw);
	hw->chip_id = (hw->params.pci.device_id & CSIO_HW_CHIP_MASK);

पूर्ण /* csio_hw_get_device_id */

/*
 * csio_hw_set_description - Set the model, description of the hw.
 * @hw: HW module.
 * @ven_id: PCI Venकरोr ID
 * @dev_id: PCI Device ID
 */
अटल व्योम
csio_hw_set_description(काष्ठा csio_hw *hw, uपूर्णांक16_t ven_id, uपूर्णांक16_t dev_id)
अणु
	uपूर्णांक32_t adap_type, prot_type;

	अगर (ven_id == CSIO_VENDOR_ID) अणु
		prot_type = (dev_id & CSIO_ASIC_DEVID_PROTO_MASK);
		adap_type = (dev_id & CSIO_ASIC_DEVID_TYPE_MASK);

		अगर (prot_type == CSIO_T5_FCOE_ASIC) अणु
			स_नकल(hw->hw_ver,
			       csio_t5_fcoe_adapters[adap_type].model_no, 16);
			स_नकल(hw->model_desc,
			       csio_t5_fcoe_adapters[adap_type].description,
			       32);
		पूर्ण अन्यथा अणु
			अक्षर tempName[32] = "Chelsio FCoE Controller";
			स_नकल(hw->model_desc, tempName, 32);
		पूर्ण
	पूर्ण
पूर्ण /* csio_hw_set_description */

/**
 * csio_hw_init - Initialize HW module.
 * @hw:		Poपूर्णांकer to HW module.
 *
 * Initialize the members of the HW module.
 */
पूर्णांक
csio_hw_init(काष्ठा csio_hw *hw)
अणु
	पूर्णांक rv = -EINVAL;
	uपूर्णांक32_t i;
	uपूर्णांक16_t ven_id, dev_id;
	काष्ठा csio_evt_msg	*evt_entry;

	INIT_LIST_HEAD(&hw->sm.sm_list);
	csio_init_state(&hw->sm, csio_hws_uninit);
	spin_lock_init(&hw->lock);
	INIT_LIST_HEAD(&hw->sln_head);

	/* Get the PCI venकरोr & device id */
	csio_hw_get_device_id(hw);

	म_नकल(hw->name, CSIO_HW_NAME);

	/* Initialize the HW chip ops T5 specअगरic ops */
	hw->chip_ops = &t5_ops;

	/* Set the model & its description */

	ven_id = hw->params.pci.venकरोr_id;
	dev_id = hw->params.pci.device_id;

	csio_hw_set_description(hw, ven_id, dev_id);

	/* Initialize शेष log level */
	hw->params.log_level = (uपूर्णांक32_t) csio_dbg_level;

	csio_set_fwevt_पूर्णांकr_idx(hw, -1);
	csio_set_nondata_पूर्णांकr_idx(hw, -1);

	/* Init all the modules: Mailbox, WorkRequest and Transport */
	अगर (csio_mbm_init(csio_hw_to_mbm(hw), hw, csio_hw_mb_समयr))
		जाओ err;

	rv = csio_wrm_init(csio_hw_to_wrm(hw), hw);
	अगर (rv)
		जाओ err_mbm_निकास;

	rv = csio_scsim_init(csio_hw_to_scsim(hw), hw);
	अगर (rv)
		जाओ err_wrm_निकास;

	rv = csio_mgmपंचांग_init(csio_hw_to_mgmपंचांग(hw), hw);
	अगर (rv)
		जाओ err_scsim_निकास;
	/* Pre-allocate evtq and initialize them */
	INIT_LIST_HEAD(&hw->evt_active_q);
	INIT_LIST_HEAD(&hw->evt_मुक्त_q);
	क्रम (i = 0; i < csio_evtq_sz; i++) अणु

		evt_entry = kzalloc(माप(काष्ठा csio_evt_msg), GFP_KERNEL);
		अगर (!evt_entry) अणु
			rv = -ENOMEM;
			csio_err(hw, "Failed to initialize eventq");
			जाओ err_evtq_cleanup;
		पूर्ण

		list_add_tail(&evt_entry->list, &hw->evt_मुक्त_q);
		CSIO_INC_STATS(hw, n_evt_मुक्तq);
	पूर्ण

	hw->dev_num = dev_num;
	dev_num++;

	वापस 0;

err_evtq_cleanup:
	csio_evtq_cleanup(hw);
	csio_mgmपंचांग_निकास(csio_hw_to_mgmपंचांग(hw));
err_scsim_निकास:
	csio_scsim_निकास(csio_hw_to_scsim(hw));
err_wrm_निकास:
	csio_wrm_निकास(csio_hw_to_wrm(hw), hw);
err_mbm_निकास:
	csio_mbm_निकास(csio_hw_to_mbm(hw));
err:
	वापस rv;
पूर्ण

/**
 * csio_hw_निकास - Un-initialize HW module.
 * @hw:		Poपूर्णांकer to HW module.
 *
 */
व्योम
csio_hw_निकास(काष्ठा csio_hw *hw)
अणु
	csio_evtq_cleanup(hw);
	csio_mgmपंचांग_निकास(csio_hw_to_mgmपंचांग(hw));
	csio_scsim_निकास(csio_hw_to_scsim(hw));
	csio_wrm_निकास(csio_hw_to_wrm(hw), hw);
	csio_mbm_निकास(csio_hw_to_mbm(hw));
पूर्ण
