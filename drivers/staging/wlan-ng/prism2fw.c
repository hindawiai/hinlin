<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1)
/* from src/prism2/करोwnload/prism2dl.c
 *
 * utility क्रम करोwnloading prism2 images moved पूर्णांकo kernelspace
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 */

/*================================================================*/
/* System Includes */
#समावेश <linux/ihex.h>
#समावेश <linux/slab.h>

/*================================================================*/
/* Local Constants */

#घोषणा PRISM2_USB_FWखाता	"prism2_ru.fw"
MODULE_FIRMWARE(PRISM2_USB_FWखाता);

#घोषणा S3DATA_MAX		5000
#घोषणा S3PLUG_MAX		200
#घोषणा S3CRC_MAX		200
#घोषणा S3INFO_MAX		50

#घोषणा S3ADDR_PLUG		(0xff000000UL)
#घोषणा S3ADDR_CRC		(0xff100000UL)
#घोषणा S3ADDR_INFO		(0xff200000UL)
#घोषणा S3ADDR_START		(0xff400000UL)

#घोषणा CHUNKS_MAX		100

#घोषणा WRITESIZE_MAX		4096

/*================================================================*/
/* Local Types */

काष्ठा s3datarec अणु
	u32 len;
	u32 addr;
	u8 checksum;
	u8 *data;
पूर्ण;

काष्ठा s3plugrec अणु
	u32 itemcode;
	u32 addr;
	u32 len;
पूर्ण;

काष्ठा s3crcrec अणु
	u32 addr;
	u32 len;
	अचिन्हित पूर्णांक करोग_लिखो;
पूर्ण;

काष्ठा s3inक्रमec अणु
	u16 len;
	u16 type;
	जोड़ अणु
		काष्ठा hfa384x_compident version;
		काष्ठा hfa384x_caplevel compat;
		u16 buildseq;
		काष्ठा hfa384x_compident platक्रमm;
	पूर्ण info;
पूर्ण;

काष्ठा pda अणु
	u8 buf[HFA384x_PDA_LEN_MAX];
	काष्ठा hfa384x_pdrec *rec[HFA384x_PDA_RECS_MAX];
	अचिन्हित पूर्णांक nrec;
पूर्ण;

काष्ठा imgchunk अणु
	u32 addr;	/* start address */
	u32 len;	/* in bytes */
	u16 crc;	/* CRC value (अगर it falls at a chunk boundary) */
	u8 *data;
पूर्ण;

/*================================================================*/
/* Local Static Definitions */

/*----------------------------------------------------------------*/
/* s-record image processing */

/* Data records */
अटल अचिन्हित पूर्णांक ns3data;
अटल काष्ठा s3datarec *s3data;

/* Plug records */
अटल अचिन्हित पूर्णांक ns3plug;
अटल काष्ठा s3plugrec s3plug[S3PLUG_MAX];

/* CRC records */
अटल अचिन्हित पूर्णांक ns3crc;
अटल काष्ठा s3crcrec s3crc[S3CRC_MAX];

/* Info records */
अटल अचिन्हित पूर्णांक ns3info;
अटल काष्ठा s3inक्रमec s3info[S3INFO_MAX];

/* S7 record (there _better_ be only one) */
अटल u32 startaddr;

/* Load image chunks */
अटल अचिन्हित पूर्णांक nfchunks;
अटल काष्ठा imgchunk fchunk[CHUNKS_MAX];

/* Note that क्रम the following pdrec_t arrays, the len and code */
/*   fields are stored in HOST byte order. The mkpdrlist() function */
/*   करोes the conversion.  */
/*----------------------------------------------------------------*/
/* PDA, built from [card|newfile]+[addfile1+addfile2...] */

अटल काष्ठा pda pda;
अटल काष्ठा hfa384x_compident nicid;
अटल काष्ठा hfa384x_caplevel rfid;
अटल काष्ठा hfa384x_caplevel macid;
अटल काष्ठा hfa384x_caplevel priid;

/*================================================================*/
/* Local Function Declarations */

अटल पूर्णांक prism2_fwapply(स्थिर काष्ठा ihex_binrec *rfptr,
			  काष्ठा wlandevice *wlandev);

अटल पूर्णांक पढ़ो_fwfile(स्थिर काष्ठा ihex_binrec *rfptr);

अटल पूर्णांक mkimage(काष्ठा imgchunk *clist, अचिन्हित पूर्णांक *ccnt);

अटल पूर्णांक पढ़ो_cardpda(काष्ठा pda *pda, काष्ठा wlandevice *wlandev);

अटल पूर्णांक mkpdrlist(काष्ठा pda *pda);

अटल पूर्णांक plugimage(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक nfchunks,
		     काष्ठा s3plugrec *s3plug, अचिन्हित पूर्णांक ns3plug,
		     काष्ठा pda *pda);

अटल पूर्णांक crcimage(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक nfchunks,
		    काष्ठा s3crcrec *s3crc, अचिन्हित पूर्णांक ns3crc);

अटल पूर्णांक ग_लिखोimage(काष्ठा wlandevice *wlandev, काष्ठा imgchunk *fchunk,
		      अचिन्हित पूर्णांक nfchunks);

अटल व्योम मुक्त_chunks(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक *nfchunks);

अटल व्योम मुक्त_srecs(व्योम);

अटल पूर्णांक validate_identity(व्योम);

/*================================================================*/
/* Function Definitions */

/*----------------------------------------------------------------
 * prism2_fwtry
 *
 * Try and get firmware पूर्णांकo memory
 *
 * Arguments:
 *	udev	usb device काष्ठाure
 *	wlandev wlan device काष्ठाure
 *
 * Returns:
 *	0	- success
 *	~0	- failure
 *----------------------------------------------------------------
 */
अटल पूर्णांक prism2_fwtry(काष्ठा usb_device *udev, काष्ठा wlandevice *wlandev)
अणु
	स्थिर काष्ठा firmware *fw_entry = शून्य;

	netdev_info(wlandev->netdev, "prism2_usb: Checking for firmware %s\n",
		    PRISM2_USB_FWखाता);
	अगर (request_ihex_firmware(&fw_entry,
				  PRISM2_USB_FWखाता, &udev->dev) != 0) अणु
		netdev_info(wlandev->netdev,
			    "prism2_usb: Firmware not available, but not essential\n");
		netdev_info(wlandev->netdev,
			    "prism2_usb: can continue to use card anyway.\n");
		वापस 1;
	पूर्ण

	netdev_info(wlandev->netdev,
		    "prism2_usb: %s will be processed, size %zu\n",
		    PRISM2_USB_FWखाता, fw_entry->size);
	prism2_fwapply((स्थिर काष्ठा ihex_binrec *)fw_entry->data, wlandev);

	release_firmware(fw_entry);
	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * prism2_fwapply
 *
 * Apply the firmware loaded पूर्णांकo memory
 *
 * Arguments:
 *	rfptr	firmware image in kernel memory
 *	wlandev device
 *
 * Returns:
 *	0	- success
 *	~0	- failure
 *----------------------------------------------------------------
 */
अटल पूर्णांक prism2_fwapply(स्थिर काष्ठा ihex_binrec *rfptr,
			  काष्ठा wlandevice *wlandev)
अणु
	चिन्हित पूर्णांक result = 0;
	काष्ठा p80211msg_करोt11req_mibget geपंचांगsg;
	काष्ठा p80211itemd *item;
	u32 *data;

	/* Initialize the data काष्ठाures */
	ns3data = 0;
	s3data = kसुस्मृति(S3DATA_MAX, माप(*s3data), GFP_KERNEL);
	अगर (!s3data) अणु
		result = -ENOMEM;
		जाओ out;
	पूर्ण

	ns3plug = 0;
	स_रखो(s3plug, 0, माप(s3plug));
	ns3crc = 0;
	स_रखो(s3crc, 0, माप(s3crc));
	ns3info = 0;
	स_रखो(s3info, 0, माप(s3info));
	startaddr = 0;

	nfchunks = 0;
	स_रखो(fchunk, 0, माप(fchunk));
	स_रखो(&nicid, 0, माप(nicid));
	स_रखो(&rfid, 0, माप(rfid));
	स_रखो(&macid, 0, माप(macid));
	स_रखो(&priid, 0, माप(priid));

	/* clear the pda and add an initial END record */
	स_रखो(&pda, 0, माप(pda));
	pda.rec[0] = (काष्ठा hfa384x_pdrec *)pda.buf;
	pda.rec[0]->len = cpu_to_le16(2);	/* len in words */
	pda.rec[0]->code = cpu_to_le16(HFA384x_PDR_END_OF_PDA);
	pda.nrec = 1;

	/*-----------------------------------------------------*/
	/* Put card पूर्णांकo fwload state */
	prism2sta_अगरstate(wlandev, P80211ENUM_अगरstate_fwload);

	/* Build the PDA we're going to use. */
	अगर (पढ़ो_cardpda(&pda, wlandev)) अणु
		netdev_err(wlandev->netdev, "load_cardpda failed, exiting.\n");
		result = 1;
		जाओ out;
	पूर्ण

	/* पढ़ो the card's PRI-SUP */
	स_रखो(&geपंचांगsg, 0, माप(geपंचांगsg));
	geपंचांगsg.msgcode = DIDMSG_DOT11REQ_MIBGET;
	geपंचांगsg.msglen = माप(geपंचांगsg);
	म_नकल(geपंचांगsg.devname, wlandev->name);

	geपंचांगsg.mibattribute.did = DIDMSG_DOT11REQ_MIBGET_MIBATTRIBUTE;
	geपंचांगsg.mibattribute.status = P80211ENUM_msgitem_status_data_ok;
	geपंचांगsg.resultcode.did = DIDMSG_DOT11REQ_MIBGET_RESULTCODE;
	geपंचांगsg.resultcode.status = P80211ENUM_msgitem_status_no_value;

	item = (काष्ठा p80211itemd *)geपंचांगsg.mibattribute.data;
	item->did = DIDMIB_P2_NIC_PRISUPRANGE;
	item->status = P80211ENUM_msgitem_status_no_value;

	data = (u32 *)item->data;

	/* DIDmsg_करोt11req_mibget */
	prism2mgmt_mibset_mibget(wlandev, &geपंचांगsg);
	अगर (geपंचांगsg.resultcode.data != P80211ENUM_resultcode_success)
		netdev_err(wlandev->netdev, "Couldn't fetch PRI-SUP info\n");

	/* Alपढ़ोy in host order */
	priid.role = *data++;
	priid.id = *data++;
	priid.variant = *data++;
	priid.bottom = *data++;
	priid.top = *data++;

	/* Read the S3 file */
	result = पढ़ो_fwfile(rfptr);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "Failed to read the data exiting.\n");
		जाओ out;
	पूर्ण

	result = validate_identity();
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Incompatible firmware image.\n");
		जाओ out;
	पूर्ण

	अगर (startaddr == 0x00000000) अणु
		netdev_err(wlandev->netdev,
			   "Can't RAM download a Flash image!\n");
		result = 1;
		जाओ out;
	पूर्ण

	/* Make the image chunks */
	result = mkimage(fchunk, &nfchunks);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to make image chunk.\n");
		जाओ मुक्त_chunks;
	पूर्ण

	/* Do any plugging */
	result = plugimage(fchunk, nfchunks, s3plug, ns3plug, &pda);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to plug data.\n");
		जाओ मुक्त_chunks;
	पूर्ण

	/* Insert any CRCs */
	result = crcimage(fchunk, nfchunks, s3crc, ns3crc);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to insert all CRCs\n");
		जाओ मुक्त_chunks;
	पूर्ण

	/* Write the image */
	result = ग_लिखोimage(wlandev, fchunk, nfchunks);
	अगर (result) अणु
		netdev_err(wlandev->netdev, "Failed to ramwrite image data.\n");
		जाओ मुक्त_chunks;
	पूर्ण

	netdev_info(wlandev->netdev, "prism2_usb: firmware loading finished.\n");

मुक्त_chunks:
	/* clear any allocated memory */
	मुक्त_chunks(fchunk, &nfchunks);
	मुक्त_srecs();

out:
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * crcimage
 *
 * Adds a CRC16 in the two bytes prior to each block identअगरied by
 * an S3 CRC record.  Currently, we करोn't actually करो a CRC we just
 * insert the value 0xC0DE in hfa384x order.
 *
 * Arguments:
 *	fchunk		Array of image chunks
 *	nfchunks	Number of image chunks
 *	s3crc		Array of crc records
 *	ns3crc		Number of crc records
 *
 * Returns:
 *	0	success
 *	~0	failure
 *----------------------------------------------------------------
 */
अटल पूर्णांक crcimage(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक nfchunks,
		    काष्ठा s3crcrec *s3crc, अचिन्हित पूर्णांक ns3crc)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;
	पूर्णांक c;
	u32 crcstart;
	u32 cstart = 0;
	u32 cend;
	u8 *dest;
	u32 chunkoff;

	क्रम (i = 0; i < ns3crc; i++) अणु
		अगर (!s3crc[i].करोग_लिखो)
			जारी;
		crcstart = s3crc[i].addr;
		/* Find chunk */
		क्रम (c = 0; c < nfchunks; c++) अणु
			cstart = fchunk[c].addr;
			cend = fchunk[c].addr + fchunk[c].len;
			/* the line below करोes an address & len match search */
			/* unक्रमtunately, I've found that the len fields of */
			/* some crc records करोn't match with the length of */
			/* the actual data, so we're not checking right now */
			/* अगर (crcstart-2 >= cstart && crcend <= cend) अवरोध; */

			/* note the -2 below, it's to make sure the chunk has */
			/* space क्रम the CRC value */
			अगर (crcstart - 2 >= cstart && crcstart < cend)
				अवरोध;
		पूर्ण
		अगर (c >= nfchunks) अणु
			pr_err("Failed to find chunk for crcrec[%d], addr=0x%06x len=%d , aborting crc.\n",
			       i, s3crc[i].addr, s3crc[i].len);
			वापस 1;
		पूर्ण

		/* Insert crc */
		pr_debug("Adding crc @ 0x%06x\n", s3crc[i].addr - 2);
		chunkoff = crcstart - cstart - 2;
		dest = fchunk[c].data + chunkoff;
		*dest = 0xde;
		*(dest + 1) = 0xc0;
	पूर्ण
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * मुक्त_chunks
 *
 * Clears the chunklist data काष्ठाures in preparation क्रम a new file.
 *
 * Arguments:
 *	none
 *
 * Returns:
 *	nothing
 *----------------------------------------------------------------
 */
अटल व्योम मुक्त_chunks(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक *nfchunks)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < *nfchunks; i++)
		kमुक्त(fchunk[i].data);

	*nfchunks = 0;
	स_रखो(fchunk, 0, माप(*fchunk));
पूर्ण

/*----------------------------------------------------------------
 * मुक्त_srecs
 *
 * Clears the srec data काष्ठाures in preparation क्रम a new file.
 *
 * Arguments:
 *	none
 *
 * Returns:
 *	nothing
 *----------------------------------------------------------------
 */
अटल व्योम मुक्त_srecs(व्योम)
अणु
	ns3data = 0;
	kमुक्त(s3data);
	ns3plug = 0;
	स_रखो(s3plug, 0, माप(s3plug));
	ns3crc = 0;
	स_रखो(s3crc, 0, माप(s3crc));
	ns3info = 0;
	स_रखो(s3info, 0, माप(s3info));
	startaddr = 0;
पूर्ण

/*----------------------------------------------------------------
 * mkimage
 *
 * Scans the currently loaded set of S records क्रम data residing
 * in contiguous memory regions.  Each contiguous region is then
 * made पूर्णांकo a 'chunk'.  This function assumes that we're building
 * a new chunk list.  Assumes the s3data items are in sorted order.
 *
 * Arguments:	none
 *
 * Returns:
 *	0	- success
 *	~0	- failure (probably an त्रुटि_सं)
 *----------------------------------------------------------------
 */
अटल पूर्णांक mkimage(काष्ठा imgchunk *clist, अचिन्हित पूर्णांक *ccnt)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक currchunk = 0;
	u32 nextaddr = 0;
	u32 s3start;
	u32 s3end;
	u32 cstart = 0;
	u32 cend;
	u32 coffset;

	/* There may alपढ़ोy be data in the chunklist */
	*ccnt = 0;

	/* Establish the location and size of each chunk */
	क्रम (i = 0; i < ns3data; i++) अणु
		अगर (s3data[i].addr == nextaddr) अणु
			/* existing chunk, grow it */
			clist[currchunk].len += s3data[i].len;
			nextaddr += s3data[i].len;
		पूर्ण अन्यथा अणु
			/* New chunk */
			(*ccnt)++;
			currchunk = *ccnt - 1;
			clist[currchunk].addr = s3data[i].addr;
			clist[currchunk].len = s3data[i].len;
			nextaddr = s3data[i].addr + s3data[i].len;
			/* Expand the chunk अगर there is a CRC record at */
			/* their beginning bound */
			क्रम (j = 0; j < ns3crc; j++) अणु
				अगर (s3crc[j].करोग_लिखो &&
				    s3crc[j].addr == clist[currchunk].addr) अणु
					clist[currchunk].addr -= 2;
					clist[currchunk].len += 2;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* We're currently assuming there aren't any overlapping chunks */
	/*  अगर this proves false, we'll need to add code to coalesce. */

	/* Allocate buffer space क्रम chunks */
	क्रम (i = 0; i < *ccnt; i++) अणु
		clist[i].data = kzalloc(clist[i].len, GFP_KERNEL);
		अगर (!clist[i].data)
			वापस 1;

		pr_debug("chunk[%d]: addr=0x%06x len=%d\n",
			 i, clist[i].addr, clist[i].len);
	पूर्ण

	/* Copy srec data to chunks */
	क्रम (i = 0; i < ns3data; i++) अणु
		s3start = s3data[i].addr;
		s3end = s3start + s3data[i].len - 1;
		क्रम (j = 0; j < *ccnt; j++) अणु
			cstart = clist[j].addr;
			cend = cstart + clist[j].len - 1;
			अगर (s3start >= cstart && s3end <= cend)
				अवरोध;
		पूर्ण
		अगर (((अचिन्हित पूर्णांक)j) >= (*ccnt)) अणु
			pr_err("s3rec(a=0x%06x,l=%d), no chunk match, exiting.\n",
			       s3start, s3data[i].len);
			वापस 1;
		पूर्ण
		coffset = s3start - cstart;
		स_नकल(clist[j].data + coffset, s3data[i].data, s3data[i].len);
	पूर्ण

	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * mkpdrlist
 *
 * Reads a raw PDA and builds an array of pdrec_t काष्ठाures.
 *
 * Arguments:
 *	pda	buffer containing raw PDA bytes
 *	pdrec	ptr to an array of pdrec_t's.  Will be filled on निकास.
 *	nrec	ptr to a variable that will contain the count of PDRs
 *
 * Returns:
 *	0	- success
 *	~0	- failure (probably an त्रुटि_सं)
 *----------------------------------------------------------------
 */
अटल पूर्णांक mkpdrlist(काष्ठा pda *pda)
अणु
	__le16 *pda16 = (__le16 *)pda->buf;
	पूर्णांक curroff;		/* in 'words' */

	pda->nrec = 0;
	curroff = 0;
	जबतक (curroff < (HFA384x_PDA_LEN_MAX / 2 - 1) &&
	       le16_to_cpu(pda16[curroff + 1]) != HFA384x_PDR_END_OF_PDA) अणु
		pda->rec[pda->nrec] = (काष्ठा hfa384x_pdrec *)&pda16[curroff];

		अगर (le16_to_cpu(pda->rec[pda->nrec]->code) ==
		    HFA384x_PDR_NICID) अणु
			स_नकल(&nicid, &pda->rec[pda->nrec]->data.nicid,
			       माप(nicid));
			le16_to_cpus(&nicid.id);
			le16_to_cpus(&nicid.variant);
			le16_to_cpus(&nicid.major);
			le16_to_cpus(&nicid.minor);
		पूर्ण
		अगर (le16_to_cpu(pda->rec[pda->nrec]->code) ==
		    HFA384x_PDR_MFISUPRANGE) अणु
			स_नकल(&rfid, &pda->rec[pda->nrec]->data.mfisuprange,
			       माप(rfid));
			le16_to_cpus(&rfid.id);
			le16_to_cpus(&rfid.variant);
			le16_to_cpus(&rfid.bottom);
			le16_to_cpus(&rfid.top);
		पूर्ण
		अगर (le16_to_cpu(pda->rec[pda->nrec]->code) ==
		    HFA384x_PDR_CFISUPRANGE) अणु
			स_नकल(&macid, &pda->rec[pda->nrec]->data.cfisuprange,
			       माप(macid));
			le16_to_cpus(&macid.id);
			le16_to_cpus(&macid.variant);
			le16_to_cpus(&macid.bottom);
			le16_to_cpus(&macid.top);
		पूर्ण

		(pda->nrec)++;
		curroff += le16_to_cpu(pda16[curroff]) + 1;
	पूर्ण
	अगर (curroff >= (HFA384x_PDA_LEN_MAX / 2 - 1)) अणु
		pr_err("no end record found or invalid lengths in PDR data, exiting. %x %d\n",
		       curroff, pda->nrec);
		वापस 1;
	पूर्ण
	pda->rec[pda->nrec] = (काष्ठा hfa384x_pdrec *)&pda16[curroff];
	(pda->nrec)++;
	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * plugimage
 *
 * Plugs the given image using the given plug records from the given
 * PDA and filename.
 *
 * Arguments:
 *	fchunk		Array of image chunks
 *	nfchunks	Number of image chunks
 *	s3plug		Array of plug records
 *	ns3plug		Number of plug records
 *	pda		Current pda data
 *
 * Returns:
 *	0	success
 *	~0	failure
 *----------------------------------------------------------------
 */
अटल पूर्णांक plugimage(काष्ठा imgchunk *fchunk, अचिन्हित पूर्णांक nfchunks,
		     काष्ठा s3plugrec *s3plug, अचिन्हित पूर्णांक ns3plug,
		     काष्ठा pda *pda)
अणु
	पूर्णांक result = 0;
	पूर्णांक i;			/* plug index */
	पूर्णांक j;			/* index of PDR or -1 अगर fname plug */
	पूर्णांक c;			/* chunk index */
	u32 pstart;
	u32 pend;
	u32 cstart = 0;
	u32 cend;
	u32 chunkoff;
	u8 *dest;

	/* क्रम each plug record */
	क्रम (i = 0; i < ns3plug; i++) अणु
		pstart = s3plug[i].addr;
		pend = s3plug[i].addr + s3plug[i].len;
		/* find the matching PDR (or filename) */
		अगर (s3plug[i].itemcode != 0xffffffffUL) अणु /* not filename */
			क्रम (j = 0; j < pda->nrec; j++) अणु
				अगर (s3plug[i].itemcode ==
				    le16_to_cpu(pda->rec[j]->code))
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			j = -1;
		पूर्ण
		अगर (j >= pda->nrec && j != -1) अणु /*  अगर no matching PDR, fail */
			pr_warn("warning: Failed to find PDR for plugrec 0x%04x.\n",
				s3plug[i].itemcode);
			जारी;	/* and move on to the next PDR */

			/* MSM: They swear that unless it's the MAC address,
			 * the serial number, or the TX calibration records,
			 * then there's reasonable शेषs in the f/w
			 * image.  Thereक्रमe, missing PDRs in the card
			 * should only be a warning, not fatal.
			 * TODO: add fatals क्रम the PDRs mentioned above.
			 */
		पूर्ण

		/* Validate plug len against PDR len */
		अगर (j != -1 && s3plug[i].len < le16_to_cpu(pda->rec[j]->len)) अणु
			pr_err("error: Plug vs. PDR len mismatch for plugrec 0x%04x, abort plugging.\n",
			       s3plug[i].itemcode);
			result = 1;
			जारी;
		पूर्ण

		/*
		 * Validate plug address against
		 * chunk data and identअगरy chunk
		 */
		क्रम (c = 0; c < nfchunks; c++) अणु
			cstart = fchunk[c].addr;
			cend = fchunk[c].addr + fchunk[c].len;
			अगर (pstart >= cstart && pend <= cend)
				अवरोध;
		पूर्ण
		अगर (c >= nfchunks) अणु
			pr_err("error: Failed to find image chunk for plugrec 0x%04x.\n",
			       s3plug[i].itemcode);
			result = 1;
			जारी;
		पूर्ण

		/* Plug data */
		chunkoff = pstart - cstart;
		dest = fchunk[c].data + chunkoff;
		pr_debug("Plugging item 0x%04x @ 0x%06x, len=%d, cnum=%d coff=0x%06x\n",
			 s3plug[i].itemcode, pstart, s3plug[i].len,
			 c, chunkoff);

		अगर (j == -1) अणु	/* plug the filename */
			स_रखो(dest, 0, s3plug[i].len);
			म_नकलन(dest, PRISM2_USB_FWखाता, s3plug[i].len - 1);
		पूर्ण अन्यथा अणु	/* plug a PDR */
			स_नकल(dest, &pda->rec[j]->data, s3plug[i].len);
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * पढ़ो_cardpda
 *
 * Sends the command क्रम the driver to पढ़ो the pda from the card
 * named in the device variable.  Upon success, the card pda is
 * stored in the "cardpda" variables.  Note that the pda काष्ठाure
 * is considered 'well formed' after this function.  That means
 * that the nrecs is valid, the rec array has been set up, and there's
 * a valid PDAEND record in the raw PDA data.
 *
 * Arguments:
 *	pda		pda काष्ठाure
 *	wlandev		device
 *
 * Returns:
 *	0	- success
 *	~0	- failure (probably an त्रुटि_सं)
 *----------------------------------------------------------------
 */
अटल पूर्णांक पढ़ो_cardpda(काष्ठा pda *pda, काष्ठा wlandevice *wlandev)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211msg_p2req_पढ़ोpda *msg;

	msg = kzalloc(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	/* set up the msg */
	msg->msgcode = DIDMSG_P2REQ_READPDA;
	msg->msglen = माप(msg);
	म_नकल(msg->devname, wlandev->name);
	msg->pda.did = DIDMSG_P2REQ_READPDA_PDA;
	msg->pda.len = HFA384x_PDA_LEN_MAX;
	msg->pda.status = P80211ENUM_msgitem_status_no_value;
	msg->resultcode.did = DIDMSG_P2REQ_READPDA_RESULTCODE;
	msg->resultcode.len = माप(u32);
	msg->resultcode.status = P80211ENUM_msgitem_status_no_value;

	अगर (prism2mgmt_पढ़ोpda(wlandev, msg) != 0) अणु
		/* prism2mgmt_पढ़ोpda prपूर्णांकs an त्रुटि_सं अगर appropriate */
		result = -1;
	पूर्ण अन्यथा अगर (msg->resultcode.data == P80211ENUM_resultcode_success) अणु
		स_नकल(pda->buf, msg->pda.data, HFA384x_PDA_LEN_MAX);
		result = mkpdrlist(pda);
	पूर्ण अन्यथा अणु
		/* resultcode must've been something other than success */
		result = -1;
	पूर्ण

	kमुक्त(msg);
	वापस result;
पूर्ण

/*----------------------------------------------------------------
 * पढ़ो_fwfile
 *
 * Reads the given fw file which should have been compiled from an srec
 * file. Each record in the fw file will either be a plain data record,
 * a start address record, or other records used क्रम plugging.
 *
 * Note that data records are expected to be sorted पूर्णांकo
 * ascending address order in the fw file.
 *
 * Note also that the start address record, originally an S7 record in
 * the srec file, is expected in the fw file to be like a data record but
 * with a certain address to make it identअगरiable.
 *
 * Here's the SREC क्रमmat that the fw should have come from:
 * S[37]nnaaaaaaaaddd...dddcc
 *
 *       nn - number of bytes starting with the address field
 * aaaaaaaa - address in पढ़ोable (or big endian) क्रमmat
 * dd....dd - 0-245 data bytes (two अक्षरs per byte)
 *       cc - checksum
 *
 * The S7 record's (there should be only one) address value माला_लो
 * converted to an S3 record with address of 0xff400000, with the
 * start address being stored as a 4 byte data word. That address is
 * the start execution address used क्रम RAM करोwnloads.
 *
 * The S3 records have a collection of subक्रमmats indicated by the
 * value of aaaaaaaa:
 *   0xff000000 - Plug record, data field क्रमmat:
 *                xxxxxxxxaaaaaaaassssssss
 *                x - PDR code number (little endian)
 *                a - Address in load image to plug (little endian)
 *                s - Length of plug data area (little endian)
 *
 *   0xff100000 - CRC16 generation record, data field क्रमmat:
 *                aaaaaaaassssssssbbbbbbbb
 *                a - Start address क्रम CRC calculation (little endian)
 *                s - Length of data to  calculate over (little endian)
 *                b - Boolean, true=ग_लिखो crc, false=करोn't ग_लिखो
 *
 *   0xff200000 - Info record, data field क्रमmat:
 *                ssssttttdd..dd
 *                s - Size in words (little endian)
 *                t - Info type (little endian), see #घोषणाs and
 *                    काष्ठा s3inक्रमec क्रम details about types.
 *                d - (s - 1) little endian words giving the contents of
 *                    the given info type.
 *
 *   0xff400000 - Start address record, data field क्रमmat:
 *                aaaaaaaa
 *                a - Address in load image to plug (little endian)
 *
 * Arguments:
 *	record	firmware image (ihex record काष्ठाure) in kernel memory
 *
 * Returns:
 *	0	- success
 *	~0	- failure (probably an त्रुटि_सं)
 *----------------------------------------------------------------
 */
अटल पूर्णांक पढ़ो_fwfile(स्थिर काष्ठा ihex_binrec *record)
अणु
	पूर्णांक		i;
	पूर्णांक		rcnt = 0;
	u16		*पंचांगpinfo;
	u16		*ptr16;
	u32		*ptr32, len, addr;

	pr_debug("Reading fw file ...\n");

	जबतक (record) अणु
		rcnt++;

		len = be16_to_cpu(record->len);
		addr = be32_to_cpu(record->addr);

		/* Poपूर्णांक पूर्णांकo data क्रम dअगरferent word lengths */
		ptr32 = (u32 *)record->data;
		ptr16 = (u16 *)record->data;

		/* parse what was an S3 srec and put it in the right array */
		चयन (addr) अणु
		हाल S3ADDR_START:
			startaddr = *ptr32;
			pr_debug("  S7 start addr, record=%d addr=0x%08x\n",
				 rcnt,
				 startaddr);
			अवरोध;
		हाल S3ADDR_PLUG:
			s3plug[ns3plug].itemcode = *ptr32;
			s3plug[ns3plug].addr = *(ptr32 + 1);
			s3plug[ns3plug].len = *(ptr32 + 2);

			pr_debug("  S3 plugrec, record=%d itemcode=0x%08x addr=0x%08x len=%d\n",
				 rcnt,
				 s3plug[ns3plug].itemcode,
				 s3plug[ns3plug].addr,
				 s3plug[ns3plug].len);

			ns3plug++;
			अगर (ns3plug == S3PLUG_MAX) अणु
				pr_err("S3 plugrec limit reached - aborting\n");
				वापस 1;
			पूर्ण
			अवरोध;
		हाल S3ADDR_CRC:
			s3crc[ns3crc].addr = *ptr32;
			s3crc[ns3crc].len = *(ptr32 + 1);
			s3crc[ns3crc].करोग_लिखो = *(ptr32 + 2);

			pr_debug("  S3 crcrec, record=%d addr=0x%08x len=%d write=0x%08x\n",
				 rcnt,
				 s3crc[ns3crc].addr,
				 s3crc[ns3crc].len,
				 s3crc[ns3crc].करोग_लिखो);
			ns3crc++;
			अगर (ns3crc == S3CRC_MAX) अणु
				pr_err("S3 crcrec limit reached - aborting\n");
				वापस 1;
			पूर्ण
			अवरोध;
		हाल S3ADDR_INFO:
			s3info[ns3info].len = *ptr16;
			s3info[ns3info].type = *(ptr16 + 1);

			pr_debug("  S3 inforec, record=%d len=0x%04x type=0x%04x\n",
				 rcnt,
				 s3info[ns3info].len,
				 s3info[ns3info].type);
			अगर (((s3info[ns3info].len - 1) * माप(u16)) >
			   माप(s3info[ns3info].info)) अणु
				pr_err("S3 inforec length too long - aborting\n");
				वापस 1;
			पूर्ण

			पंचांगpinfo = (u16 *)&s3info[ns3info].info.version;
			pr_debug("            info=");
			क्रम (i = 0; i < s3info[ns3info].len - 1; i++) अणु
				पंचांगpinfo[i] = *(ptr16 + 2 + i);
				pr_debug("%04x ", पंचांगpinfo[i]);
			पूर्ण
			pr_debug("\n");

			ns3info++;
			अगर (ns3info == S3INFO_MAX) अणु
				pr_err("S3 inforec limit reached - aborting\n");
				वापस 1;
			पूर्ण
			अवरोध;
		शेष:	/* Data record */
			s3data[ns3data].addr = addr;
			s3data[ns3data].len = len;
			s3data[ns3data].data = (uपूर्णांक8_t *)record->data;
			ns3data++;
			अगर (ns3data == S3DATA_MAX) अणु
				pr_err("S3 datarec limit reached - aborting\n");
				वापस 1;
			पूर्ण
			अवरोध;
		पूर्ण
		record = ihex_next_binrec(record);
	पूर्ण
	वापस 0;
पूर्ण

/*----------------------------------------------------------------
 * ग_लिखोimage
 *
 * Takes the chunks, builds p80211 messages and sends them करोwn
 * to the driver क्रम writing to the card.
 *
 * Arguments:
 *	wlandev		device
 *	fchunk		Array of image chunks
 *	nfchunks	Number of image chunks
 *
 * Returns:
 *	0	success
 *	~0	failure
 *----------------------------------------------------------------
 */
अटल पूर्णांक ग_लिखोimage(काष्ठा wlandevice *wlandev, काष्ठा imgchunk *fchunk,
		      अचिन्हित पूर्णांक nfchunks)
अणु
	पूर्णांक result = 0;
	काष्ठा p80211msg_p2req_ramdl_state *rsपंचांगsg;
	काष्ठा p80211msg_p2req_ramdl_ग_लिखो *rwrmsg;
	u32 resultcode;
	पूर्णांक i;
	पूर्णांक j;
	अचिन्हित पूर्णांक nग_लिखोs;
	u32 curroff;
	u32 currlen;
	u32 currdaddr;

	rsपंचांगsg = kzalloc(माप(*rsपंचांगsg), GFP_KERNEL);
	rwrmsg = kzalloc(माप(*rwrmsg), GFP_KERNEL);
	अगर (!rsपंचांगsg || !rwrmsg) अणु
		kमुक्त(rsपंचांगsg);
		kमुक्त(rwrmsg);
		netdev_err(wlandev->netdev,
			   "%s: no memory for firmware download, aborting download\n",
			   __func__);
		वापस -ENOMEM;
	पूर्ण

	/* Initialize the messages */
	म_नकल(rsपंचांगsg->devname, wlandev->name);
	rsपंचांगsg->msgcode = DIDMSG_P2REQ_RAMDL_STATE;
	rsपंचांगsg->msglen = माप(*rsपंचांगsg);
	rsपंचांगsg->enable.did = DIDMSG_P2REQ_RAMDL_STATE_ENABLE;
	rsपंचांगsg->exeaddr.did = DIDMSG_P2REQ_RAMDL_STATE_EXEADDR;
	rsपंचांगsg->resultcode.did = DIDMSG_P2REQ_RAMDL_STATE_RESULTCODE;
	rsपंचांगsg->enable.status = P80211ENUM_msgitem_status_data_ok;
	rsपंचांगsg->exeaddr.status = P80211ENUM_msgitem_status_data_ok;
	rsपंचांगsg->resultcode.status = P80211ENUM_msgitem_status_no_value;
	rsपंचांगsg->enable.len = माप(u32);
	rsपंचांगsg->exeaddr.len = माप(u32);
	rsपंचांगsg->resultcode.len = माप(u32);

	म_नकल(rwrmsg->devname, wlandev->name);
	rwrmsg->msgcode = DIDMSG_P2REQ_RAMDL_WRITE;
	rwrmsg->msglen = माप(*rwrmsg);
	rwrmsg->addr.did = DIDMSG_P2REQ_RAMDL_WRITE_ADDR;
	rwrmsg->len.did = DIDMSG_P2REQ_RAMDL_WRITE_LEN;
	rwrmsg->data.did = DIDMSG_P2REQ_RAMDL_WRITE_DATA;
	rwrmsg->resultcode.did = DIDMSG_P2REQ_RAMDL_WRITE_RESULTCODE;
	rwrmsg->addr.status = P80211ENUM_msgitem_status_data_ok;
	rwrmsg->len.status = P80211ENUM_msgitem_status_data_ok;
	rwrmsg->data.status = P80211ENUM_msgitem_status_data_ok;
	rwrmsg->resultcode.status = P80211ENUM_msgitem_status_no_value;
	rwrmsg->addr.len = माप(u32);
	rwrmsg->len.len = माप(u32);
	rwrmsg->data.len = WRITESIZE_MAX;
	rwrmsg->resultcode.len = माप(u32);

	/* Send xxx_state(enable) */
	pr_debug("Sending dl_state(enable) message.\n");
	rsपंचांगsg->enable.data = P80211ENUM_truth_true;
	rsपंचांगsg->exeaddr.data = startaddr;

	result = prism2mgmt_ramdl_state(wlandev, rsपंचांगsg);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "%s state enable failed w/ result=%d, aborting download\n",
			   __func__, result);
		जाओ मुक्त_result;
	पूर्ण
	resultcode = rsपंचांगsg->resultcode.data;
	अगर (resultcode != P80211ENUM_resultcode_success) अणु
		netdev_err(wlandev->netdev,
			   "%s()->xxxdl_state msg indicates failure, w/ resultcode=%d, aborting download.\n",
			   __func__, resultcode);
		result = 1;
		जाओ मुक्त_result;
	पूर्ण

	/* Now, loop through the data chunks and send WRITESIZE_MAX data */
	क्रम (i = 0; i < nfchunks; i++) अणु
		nग_लिखोs = fchunk[i].len / WRITESIZE_MAX;
		nग_लिखोs += (fchunk[i].len % WRITESIZE_MAX) ? 1 : 0;
		curroff = 0;
		क्रम (j = 0; j < nग_लिखोs; j++) अणु
			/* TODO Move this to a separate function */
			पूर्णांक lenleft = fchunk[i].len - (WRITESIZE_MAX * j);

			अगर (fchunk[i].len > WRITESIZE_MAX)
				currlen = WRITESIZE_MAX;
			अन्यथा
				currlen = lenleft;
			curroff = j * WRITESIZE_MAX;
			currdaddr = fchunk[i].addr + curroff;
			/* Setup the message */
			rwrmsg->addr.data = currdaddr;
			rwrmsg->len.data = currlen;
			स_नकल(rwrmsg->data.data,
			       fchunk[i].data + curroff, currlen);

			/* Send flashdl_ग_लिखो(pda) */
			pr_debug
			    ("Sending xxxdl_write message addr=%06x len=%d.\n",
			     currdaddr, currlen);

			result = prism2mgmt_ramdl_ग_लिखो(wlandev, rwrmsg);

			/* Check the results */
			अगर (result) अणु
				netdev_err(wlandev->netdev,
					   "%s chunk write failed w/ result=%d, aborting download\n",
					   __func__, result);
				जाओ मुक्त_result;
			पूर्ण
			resultcode = rsपंचांगsg->resultcode.data;
			अगर (resultcode != P80211ENUM_resultcode_success) अणु
				pr_err("%s()->xxxdl_write msg indicates failure, w/ resultcode=%d, aborting download.\n",
				       __func__, resultcode);
				result = 1;
				जाओ मुक्त_result;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Send xxx_state(disable) */
	pr_debug("Sending dl_state(disable) message.\n");
	rsपंचांगsg->enable.data = P80211ENUM_truth_false;
	rsपंचांगsg->exeaddr.data = 0;

	result = prism2mgmt_ramdl_state(wlandev, rsपंचांगsg);
	अगर (result) अणु
		netdev_err(wlandev->netdev,
			   "%s state disable failed w/ result=%d, aborting download\n",
			   __func__, result);
		जाओ मुक्त_result;
	पूर्ण
	resultcode = rsपंचांगsg->resultcode.data;
	अगर (resultcode != P80211ENUM_resultcode_success) अणु
		netdev_err(wlandev->netdev,
			   "%s()->xxxdl_state msg indicates failure, w/ resultcode=%d, aborting download.\n",
			   __func__, resultcode);
		result = 1;
		जाओ मुक्त_result;
	पूर्ण

मुक्त_result:
	kमुक्त(rsपंचांगsg);
	kमुक्त(rwrmsg);
	वापस result;
पूर्ण

अटल पूर्णांक validate_identity(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक result = 1;
	पूर्णांक trump = 0;

	pr_debug("NIC ID: %#x v%d.%d.%d\n",
		 nicid.id, nicid.major, nicid.minor, nicid.variant);
	pr_debug("MFI ID: %#x v%d %d->%d\n",
		 rfid.id, rfid.variant, rfid.bottom, rfid.top);
	pr_debug("CFI ID: %#x v%d %d->%d\n",
		 macid.id, macid.variant, macid.bottom, macid.top);
	pr_debug("PRI ID: %#x v%d %d->%d\n",
		 priid.id, priid.variant, priid.bottom, priid.top);

	क्रम (i = 0; i < ns3info; i++) अणु
		चयन (s3info[i].type) अणु
		हाल 1:
			pr_debug("Version:  ID %#x %d.%d.%d\n",
				 s3info[i].info.version.id,
				 s3info[i].info.version.major,
				 s3info[i].info.version.minor,
				 s3info[i].info.version.variant);
			अवरोध;
		हाल 2:
			pr_debug("Compat: Role %#x Id %#x v%d %d->%d\n",
				 s3info[i].info.compat.role,
				 s3info[i].info.compat.id,
				 s3info[i].info.compat.variant,
				 s3info[i].info.compat.bottom,
				 s3info[i].info.compat.top);

			/* MAC compat range */
			अगर ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 2)) अणु
				अगर (s3info[i].info.compat.variant !=
				    macid.variant) अणु
					result = 2;
				पूर्ण
			पूर्ण

			/* PRI compat range */
			अगर ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 3)) अणु
				अगर ((s3info[i].info.compat.bottom >
				     priid.top) ||
				    (s3info[i].info.compat.top <
				     priid.bottom)) अणु
					result = 3;
				पूर्ण
			पूर्ण
			/* SEC compat range */
			अगर ((s3info[i].info.compat.role == 1) &&
			    (s3info[i].info.compat.id == 4)) अणु
				/* FIXME: isn't something missing here? */
			पूर्ण

			अवरोध;
		हाल 3:
			pr_debug("Seq: %#x\n", s3info[i].info.buildseq);

			अवरोध;
		हाल 4:
			pr_debug("Platform:  ID %#x %d.%d.%d\n",
				 s3info[i].info.version.id,
				 s3info[i].info.version.major,
				 s3info[i].info.version.minor,
				 s3info[i].info.version.variant);

			अगर (nicid.id != s3info[i].info.version.id)
				जारी;
			अगर (nicid.major != s3info[i].info.version.major)
				जारी;
			अगर (nicid.minor != s3info[i].info.version.minor)
				जारी;
			अगर ((nicid.variant != s3info[i].info.version.variant) &&
			    (nicid.id != 0x8008))
				जारी;

			trump = 1;
			अवरोध;
		हाल 0x8001:
			pr_debug("name inforec len %d\n", s3info[i].len);

			अवरोध;
		शेष:
			pr_debug("Unknown inforec type %d\n", s3info[i].type);
		पूर्ण
	पूर्ण
	/* walk through */

	अगर (trump && (result != 2))
		result = 0;
	वापस result;
पूर्ण
