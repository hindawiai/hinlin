<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qib.h"

/*
 * Functions specअगरic to the serial EEPROM on cards handled by ib_qib.
 * The actual serail पूर्णांकerface code is in qib_twsi.c. This file is a client
 */

/**
 * qib_eeprom_पढ़ो - receives bytes from the eeprom via I2C
 * @dd: the qlogic_ib device
 * @eeprom_offset: address to पढ़ो from
 * @buff: where to store result
 * @len: number of bytes to receive
 */
पूर्णांक qib_eeprom_पढ़ो(काष्ठा qib_devdata *dd, u8 eeprom_offset,
		    व्योम *buff, पूर्णांक len)
अणु
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&dd->eep_lock);
	अगर (!ret) अणु
		ret = qib_twsi_reset(dd);
		अगर (ret)
			qib_dev_err(dd, "EEPROM Reset for read failed\n");
		अन्यथा
			ret = qib_twsi_blk_rd(dd, dd->twsi_eeprom_dev,
					      eeprom_offset, buff, len);
		mutex_unlock(&dd->eep_lock);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Actually update the eeprom, first करोing ग_लिखो enable अगर
 * needed, then restoring ग_लिखो enable state.
 * Must be called with eep_lock held
 */
अटल पूर्णांक eeprom_ग_लिखो_with_enable(काष्ठा qib_devdata *dd, u8 offset,
		     स्थिर व्योम *buf, पूर्णांक len)
अणु
	पूर्णांक ret, pwen;

	pwen = dd->f_eeprom_wen(dd, 1);
	ret = qib_twsi_reset(dd);
	अगर (ret)
		qib_dev_err(dd, "EEPROM Reset for write failed\n");
	अन्यथा
		ret = qib_twsi_blk_wr(dd, dd->twsi_eeprom_dev,
				      offset, buf, len);
	dd->f_eeprom_wen(dd, pwen);
	वापस ret;
पूर्ण

/**
 * qib_eeprom_ग_लिखो - ग_लिखोs data to the eeprom via I2C
 * @dd: the qlogic_ib device
 * @eeprom_offset: where to place data
 * @buff: data to ग_लिखो
 * @len: number of bytes to ग_लिखो
 */
पूर्णांक qib_eeprom_ग_लिखो(काष्ठा qib_devdata *dd, u8 eeprom_offset,
		     स्थिर व्योम *buff, पूर्णांक len)
अणु
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&dd->eep_lock);
	अगर (!ret) अणु
		ret = eeprom_ग_लिखो_with_enable(dd, eeprom_offset, buff, len);
		mutex_unlock(&dd->eep_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 flash_csum(काष्ठा qib_flash *अगरp, पूर्णांक adjust)
अणु
	u8 *ip = (u8 *) अगरp;
	u8 csum = 0, len;

	/*
	 * Limit length checksummed to max length of actual data.
	 * Checksum of erased eeprom will still be bad, but we aव्योम
	 * पढ़ोing past the end of the buffer we were passed.
	 */
	len = अगरp->अगर_length;
	अगर (len > माप(काष्ठा qib_flash))
		len = माप(काष्ठा qib_flash);
	जबतक (len--)
		csum += *ip++;
	csum -= अगरp->अगर_csum;
	csum = ~csum;
	अगर (adjust)
		अगरp->अगर_csum = csum;

	वापस csum;
पूर्ण

/**
 * qib_get_eeprom_info- get the GUID et al. from the TSWI EEPROM device
 * @dd: the qlogic_ib device
 *
 * We have the capability to use the nguid field, and get
 * the guid from the first chip's flash, to use क्रम all of them.
 */
व्योम qib_get_eeprom_info(काष्ठा qib_devdata *dd)
अणु
	व्योम *buf;
	काष्ठा qib_flash *अगरp;
	__be64 guid;
	पूर्णांक len, eep_stat;
	u8 csum, *bguid;
	पूर्णांक t = dd->unit;
	काष्ठा qib_devdata *dd0 = qib_lookup(0);

	अगर (t && dd0->nguid > 1 && t <= dd0->nguid) अणु
		u8 oguid;

		dd->base_guid = dd0->base_guid;
		bguid = (u8 *) &dd->base_guid;

		oguid = bguid[7];
		bguid[7] += t;
		अगर (oguid > bguid[7]) अणु
			अगर (bguid[6] == 0xff) अणु
				अगर (bguid[5] == 0xff) अणु
					qib_dev_err(dd,
						    "Can't set GUID from base, wraps to OUI!\n");
					dd->base_guid = 0;
					जाओ bail;
				पूर्ण
				bguid[5]++;
			पूर्ण
			bguid[6]++;
		पूर्ण
		dd->nguid = 1;
		जाओ bail;
	पूर्ण

	/*
	 * Read full flash, not just currently used part, since it may have
	 * been written with a newer definition.
	 * */
	len = माप(काष्ठा qib_flash);
	buf = vदो_स्मृति(len);
	अगर (!buf)
		जाओ bail;

	/*
	 * Use "public" eeprom पढ़ो function, which करोes locking and
	 * figures out device. This will migrate to chip-specअगरic.
	 */
	eep_stat = qib_eeprom_पढ़ो(dd, 0, buf, len);

	अगर (eep_stat) अणु
		qib_dev_err(dd, "Failed reading GUID from eeprom\n");
		जाओ करोne;
	पूर्ण
	अगरp = (काष्ठा qib_flash *)buf;

	csum = flash_csum(अगरp, 0);
	अगर (csum != अगरp->अगर_csum) अणु
		qib_devinfo(dd->pcidev,
			"Bad I2C flash checksum: 0x%x, not 0x%x\n",
			csum, अगरp->अगर_csum);
		जाओ करोne;
	पूर्ण
	अगर (*(__be64 *) अगरp->अगर_guid == cpu_to_be64(0) ||
	    *(__be64 *) अगरp->अगर_guid == ~cpu_to_be64(0)) अणु
		qib_dev_err(dd,
			"Invalid GUID %llx from flash; ignoring\n",
			*(अचिन्हित दीर्घ दीर्घ *) अगरp->अगर_guid);
		/* करोn't allow GUID if all 0 or all 1's */
		जाओ करोne;
	पूर्ण

	/* complain, but allow it */
	अगर (*(u64 *) अगरp->अगर_guid == 0x100007511000000ULL)
		qib_devinfo(dd->pcidev,
			"Warning, GUID %llx is default, probably not correct!\n",
			*(अचिन्हित दीर्घ दीर्घ *) अगरp->अगर_guid);

	bguid = अगरp->अगर_guid;
	अगर (!bguid[0] && !bguid[1] && !bguid[2]) अणु
		/*
		 * Original incorrect GUID क्रमmat in flash; fix in
		 * core copy, by shअगरting up 2 octets; करोn't need to
		 * change top octet, since both it and shअगरted are 0.
		 */
		bguid[1] = bguid[3];
		bguid[2] = bguid[4];
		bguid[3] = 0;
		bguid[4] = 0;
		guid = *(__be64 *) अगरp->अगर_guid;
	पूर्ण अन्यथा
		guid = *(__be64 *) अगरp->अगर_guid;
	dd->base_guid = guid;
	dd->nguid = अगरp->अगर_numguid;
	/*
	 * Things are slightly complicated by the desire to transparently
	 * support both the Pathscale 10-digit serial number and the QLogic
	 * 13-अक्षरacter version.
	 */
	अगर ((अगरp->अगर_fversion > 1) && अगरp->अगर_sprefix[0] &&
	    ((u8 *) अगरp->अगर_sprefix)[0] != 0xFF) अणु
		अक्षर *snp = dd->serial;

		/*
		 * This board has a Serial-prefix, which is stored
		 * अन्यथाwhere क्रम backward-compatibility.
		 */
		स_नकल(snp, अगरp->अगर_sprefix, माप(अगरp->अगर_sprefix));
		snp[माप(अगरp->अगर_sprefix)] = '\0';
		len = म_माप(snp);
		snp += len;
		len = माप(dd->serial) - len;
		अगर (len > माप(अगरp->अगर_serial))
			len = माप(अगरp->अगर_serial);
		स_नकल(snp, अगरp->अगर_serial, len);
	पूर्ण अन्यथा अणु
		स_नकल(dd->serial, अगरp->अगर_serial, माप(अगरp->अगर_serial));
	पूर्ण
	अगर (!म_माला(अगरp->अगर_comment, "Tested successfully"))
		qib_dev_err(dd,
			"Board SN %s did not pass functional test: %s\n",
			dd->serial, अगरp->अगर_comment);

करोne:
	vमुक्त(buf);

bail:;
पूर्ण

