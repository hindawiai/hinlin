<शैली गुरु>
/* $Id: capiutil.c,v 1.13.6.4 2001/09/23 22:24:33 kai Exp $
 *
 * CAPI 2.0 convert capi message to capi message काष्ठा
 *
 * From CAPI 2.0 Development Kit AVM 1995 (msg.c)
 * Rewritten क्रम Linux 1996 by Carsten Paeth <calle@calle.de>
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/isdn/capiutil.h>
#समावेश <linux/slab.h>

#समावेश "kcapi.h"

/* from CAPI2.0 DDK AVM Berlin GmbH */

प्रकार काष्ठा अणु
	पूर्णांक typ;
	माप_प्रकार off;
पूर्ण _cdef;

#घोषणा _CBYTE	       1
#घोषणा _CWORD	       2
#घोषणा _CDWORD        3
#घोषणा _CSTRUCT       4
#घोषणा _CMSTRUCT      5
#घोषणा _CEND	       6

अटल _cdef cdef[] =
अणु
	/*00 */
	अणु_CENDपूर्ण,
	/*01 */
	अणु_CENDपूर्ण,
	/*02 */
	अणु_CENDपूर्ण,
	/*03 */
	अणु_CDWORD, दुरत्व(_cmsg, adr.adrController)पूर्ण,
	/*04 */
	अणु_CMSTRUCT, दुरत्व(_cmsg, AdditionalInfo)पूर्ण,
	/*05 */
	अणु_CSTRUCT, दुरत्व(_cmsg, B1configuration)पूर्ण,
	/*06 */
	अणु_CWORD, दुरत्व(_cmsg, B1protocol)पूर्ण,
	/*07 */
	अणु_CSTRUCT, दुरत्व(_cmsg, B2configuration)पूर्ण,
	/*08 */
	अणु_CWORD, दुरत्व(_cmsg, B2protocol)पूर्ण,
	/*09 */
	अणु_CSTRUCT, दुरत्व(_cmsg, B3configuration)पूर्ण,
	/*0a */
	अणु_CWORD, दुरत्व(_cmsg, B3protocol)पूर्ण,
	/*0b */
	अणु_CSTRUCT, दुरत्व(_cmsg, BC)पूर्ण,
	/*0c */
	अणु_CSTRUCT, दुरत्व(_cmsg, BChannelinक्रमmation)पूर्ण,
	/*0d */
	अणु_CMSTRUCT, दुरत्व(_cmsg, BProtocol)पूर्ण,
	/*0e */
	अणु_CSTRUCT, दुरत्व(_cmsg, CalledPartyNumber)पूर्ण,
	/*0f */
	अणु_CSTRUCT, दुरत्व(_cmsg, CalledPartySubaddress)पूर्ण,
	/*10 */
	अणु_CSTRUCT, दुरत्व(_cmsg, CallingPartyNumber)पूर्ण,
	/*11 */
	अणु_CSTRUCT, दुरत्व(_cmsg, CallingPartySubaddress)पूर्ण,
	/*12 */
	अणु_CDWORD, दुरत्व(_cmsg, CIPmask)पूर्ण,
	/*13 */
	अणु_CDWORD, दुरत्व(_cmsg, CIPmask2)पूर्ण,
	/*14 */
	अणु_CWORD, दुरत्व(_cmsg, CIPValue)पूर्ण,
	/*15 */
	अणु_CDWORD, दुरत्व(_cmsg, Class)पूर्ण,
	/*16 */
	अणु_CSTRUCT, दुरत्व(_cmsg, ConnectedNumber)पूर्ण,
	/*17 */
	अणु_CSTRUCT, दुरत्व(_cmsg, ConnectedSubaddress)पूर्ण,
	/*18 */
	अणु_CDWORD, दुरत्व(_cmsg, Data)पूर्ण,
	/*19 */
	अणु_CWORD, दुरत्व(_cmsg, DataHandle)पूर्ण,
	/*1a */
	अणु_CWORD, दुरत्व(_cmsg, DataLength)पूर्ण,
	/*1b */
	अणु_CSTRUCT, दुरत्व(_cmsg, FacilityConfirmationParameter)पूर्ण,
	/*1c */
	अणु_CSTRUCT, दुरत्व(_cmsg, Facilitydataarray)पूर्ण,
	/*1d */
	अणु_CSTRUCT, दुरत्व(_cmsg, FacilityIndicationParameter)पूर्ण,
	/*1e */
	अणु_CSTRUCT, दुरत्व(_cmsg, FacilityRequestParameter)पूर्ण,
	/*1f */
	अणु_CWORD, दुरत्व(_cmsg, FacilitySelector)पूर्ण,
	/*20 */
	अणु_CWORD, दुरत्व(_cmsg, Flags)पूर्ण,
	/*21 */
	अणु_CDWORD, दुरत्व(_cmsg, Function)पूर्ण,
	/*22 */
	अणु_CSTRUCT, दुरत्व(_cmsg, HLC)पूर्ण,
	/*23 */
	अणु_CWORD, दुरत्व(_cmsg, Info)पूर्ण,
	/*24 */
	अणु_CSTRUCT, दुरत्व(_cmsg, InfoElement)पूर्ण,
	/*25 */
	अणु_CDWORD, दुरत्व(_cmsg, InfoMask)पूर्ण,
	/*26 */
	अणु_CWORD, दुरत्व(_cmsg, InfoNumber)पूर्ण,
	/*27 */
	अणु_CSTRUCT, दुरत्व(_cmsg, Keypadfacility)पूर्ण,
	/*28 */
	अणु_CSTRUCT, दुरत्व(_cmsg, LLC)पूर्ण,
	/*29 */
	अणु_CSTRUCT, दुरत्व(_cmsg, ManuData)पूर्ण,
	/*2a */
	अणु_CDWORD, दुरत्व(_cmsg, ManuID)पूर्ण,
	/*2b */
	अणु_CSTRUCT, दुरत्व(_cmsg, NCPI)पूर्ण,
	/*2c */
	अणु_CWORD, दुरत्व(_cmsg, Reason)पूर्ण,
	/*2d */
	अणु_CWORD, दुरत्व(_cmsg, Reason_B3)पूर्ण,
	/*2e */
	अणु_CWORD, दुरत्व(_cmsg, Reject)पूर्ण,
	/*2f */
	अणु_CSTRUCT, दुरत्व(_cmsg, Useruserdata)पूर्ण
पूर्ण;

अटल अचिन्हित अक्षर *cpars[] =
अणु
	/* ALERT_REQ */ [0x01] = "\x03\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_REQ */ [0x02] = "\x03\x14\x0e\x10\x0f\x11\x0d\x06\x08\x0a\x05\x07\x09\x01\x0b\x28\x22\x04\x0c\x27\x2f\x1c\x01\x01",
	/* DISCONNECT_REQ */ [0x04] = "\x03\x04\x0c\x27\x2f\x1c\x01\x01",
	/* LISTEN_REQ */ [0x05] = "\x03\x25\x12\x13\x10\x11\x01",
	/* INFO_REQ */ [0x08] = "\x03\x0e\x04\x0c\x27\x2f\x1c\x01\x01",
	/* FACILITY_REQ */ [0x09] = "\x03\x1f\x1e\x01",
	/* SELECT_B_PROTOCOL_REQ */ [0x0a] = "\x03\x0d\x06\x08\x0a\x05\x07\x09\x01\x01",
	/* CONNECT_B3_REQ */ [0x0b] = "\x03\x2b\x01",
	/* DISCONNECT_B3_REQ */ [0x0d] = "\x03\x2b\x01",
	/* DATA_B3_REQ */ [0x0f] = "\x03\x18\x1a\x19\x20\x01",
	/* RESET_B3_REQ */ [0x10] = "\x03\x2b\x01",
	/* ALERT_CONF */ [0x13] = "\x03\x23\x01",
	/* CONNECT_CONF */ [0x14] = "\x03\x23\x01",
	/* DISCONNECT_CONF */ [0x16] = "\x03\x23\x01",
	/* LISTEN_CONF */ [0x17] = "\x03\x23\x01",
	/* MANUFACTURER_REQ */ [0x18] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_CONF */ [0x1a] = "\x03\x23\x01",
	/* FACILITY_CONF */ [0x1b] = "\x03\x23\x1f\x1b\x01",
	/* SELECT_B_PROTOCOL_CONF */ [0x1c] = "\x03\x23\x01",
	/* CONNECT_B3_CONF */ [0x1d] = "\x03\x23\x01",
	/* DISCONNECT_B3_CONF */ [0x1f] = "\x03\x23\x01",
	/* DATA_B3_CONF */ [0x21] = "\x03\x19\x23\x01",
	/* RESET_B3_CONF */ [0x22] = "\x03\x23\x01",
	/* CONNECT_IND */ [0x26] = "\x03\x14\x0e\x10\x0f\x11\x0b\x28\x22\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_ACTIVE_IND */ [0x27] = "\x03\x16\x17\x28\x01",
	/* DISCONNECT_IND */ [0x28] = "\x03\x2c\x01",
	/* MANUFACTURER_CONF */ [0x2a] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_IND */ [0x2c] = "\x03\x26\x24\x01",
	/* FACILITY_IND */ [0x2d] = "\x03\x1f\x1d\x01",
	/* CONNECT_B3_IND */ [0x2f] = "\x03\x2b\x01",
	/* CONNECT_B3_ACTIVE_IND */ [0x30] = "\x03\x2b\x01",
	/* DISCONNECT_B3_IND */ [0x31] = "\x03\x2d\x2b\x01",
	/* DATA_B3_IND */ [0x33] = "\x03\x18\x1a\x19\x20\x01",
	/* RESET_B3_IND */ [0x34] = "\x03\x2b\x01",
	/* CONNECT_B3_T90_ACTIVE_IND */ [0x35] = "\x03\x2b\x01",
	/* CONNECT_RESP */ [0x38] = "\x03\x2e\x0d\x06\x08\x0a\x05\x07\x09\x01\x16\x17\x28\x04\x0c\x27\x2f\x1c\x01\x01",
	/* CONNECT_ACTIVE_RESP */ [0x39] = "\x03\x01",
	/* DISCONNECT_RESP */ [0x3a] = "\x03\x01",
	/* MANUFACTURER_IND */ [0x3c] = "\x03\x2a\x15\x21\x29\x01",
	/* INFO_RESP */ [0x3e] = "\x03\x01",
	/* FACILITY_RESP */ [0x3f] = "\x03\x1f\x01",
	/* CONNECT_B3_RESP */ [0x41] = "\x03\x2e\x2b\x01",
	/* CONNECT_B3_ACTIVE_RESP */ [0x42] = "\x03\x01",
	/* DISCONNECT_B3_RESP */ [0x43] = "\x03\x01",
	/* DATA_B3_RESP */ [0x45] = "\x03\x19\x01",
	/* RESET_B3_RESP */ [0x46] = "\x03\x01",
	/* CONNECT_B3_T90_ACTIVE_RESP */ [0x47] = "\x03\x01",
	/* MANUFACTURER_RESP */ [0x4e] = "\x03\x2a\x15\x21\x29\x01",
पूर्ण;

/*-------------------------------------------------------*/

#घोषणा byteTLcpy(x, y)         *(u8 *)(x) = *(u8 *)(y);
#घोषणा wordTLcpy(x, y)         *(u16 *)(x) = *(u16 *)(y);
#घोषणा dwordTLcpy(x, y)        स_नकल(x, y, 4);
#घोषणा काष्ठाTLcpy(x, y, l)    स_नकल(x, y, l)
#घोषणा काष्ठाTLcpyovl(x, y, l) स_हटाओ(x, y, l)

#घोषणा byteTRcpy(x, y)         *(u8 *)(y) = *(u8 *)(x);
#घोषणा wordTRcpy(x, y)         *(u16 *)(y) = *(u16 *)(x);
#घोषणा dwordTRcpy(x, y)        स_नकल(y, x, 4);
#घोषणा काष्ठाTRcpy(x, y, l)    स_नकल(y, x, l)
#घोषणा काष्ठाTRcpyovl(x, y, l) स_हटाओ(y, x, l)

/*-------------------------------------------------------*/
अटल अचिन्हित command_2_index(u8 c, u8 sc)
अणु
	अगर (c & 0x80)
		c = 0x9 + (c & 0x0f);
	अन्यथा अगर (c == 0x41)
		c = 0x9 + 0x1;
	अगर (c > 0x18)
		c = 0x00;
	वापस (sc & 3) * (0x9 + 0x9) + c;
पूर्ण

/**
 * capi_cmd2par() - find parameter string क्रम CAPI 2.0 command/subcommand
 * @cmd:	command number
 * @subcmd:	subcommand number
 *
 * Return value: अटल string, शून्य अगर command/subcommand unknown
 */

अटल अचिन्हित अक्षर *capi_cmd2par(u8 cmd, u8 subcmd)
अणु
	वापस cpars[command_2_index(cmd, subcmd)];
पूर्ण

/*-------------------------------------------------------*/
#घोषणा TYP (cdef[cmsg->par[cmsg->p]].typ)
#घोषणा OFF (((u8 *)cmsg) + cdef[cmsg->par[cmsg->p]].off)

अटल व्योम jumpcकाष्ठा(_cmsg *cmsg)
अणु
	अचिन्हित layer;
	क्रम (cmsg->p++, layer = 1; layer;) अणु
		/* $$$$$ निश्चित (cmsg->p); */
		cmsg->p++;
		चयन (TYP) अणु
		हाल _CMSTRUCT:
			layer++;
			अवरोध;
		हाल _CEND:
			layer--;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*-------------------------------------------------------*/

अटल अक्षर *mnames[] =
अणु
	[0x01] = "ALERT_REQ",
	[0x02] = "CONNECT_REQ",
	[0x04] = "DISCONNECT_REQ",
	[0x05] = "LISTEN_REQ",
	[0x08] = "INFO_REQ",
	[0x09] = "FACILITY_REQ",
	[0x0a] = "SELECT_B_PROTOCOL_REQ",
	[0x0b] = "CONNECT_B3_REQ",
	[0x0d] = "DISCONNECT_B3_REQ",
	[0x0f] = "DATA_B3_REQ",
	[0x10] = "RESET_B3_REQ",
	[0x13] = "ALERT_CONF",
	[0x14] = "CONNECT_CONF",
	[0x16] = "DISCONNECT_CONF",
	[0x17] = "LISTEN_CONF",
	[0x18] = "MANUFACTURER_REQ",
	[0x1a] = "INFO_CONF",
	[0x1b] = "FACILITY_CONF",
	[0x1c] = "SELECT_B_PROTOCOL_CONF",
	[0x1d] = "CONNECT_B3_CONF",
	[0x1f] = "DISCONNECT_B3_CONF",
	[0x21] = "DATA_B3_CONF",
	[0x22] = "RESET_B3_CONF",
	[0x26] = "CONNECT_IND",
	[0x27] = "CONNECT_ACTIVE_IND",
	[0x28] = "DISCONNECT_IND",
	[0x2a] = "MANUFACTURER_CONF",
	[0x2c] = "INFO_IND",
	[0x2d] = "FACILITY_IND",
	[0x2f] = "CONNECT_B3_IND",
	[0x30] = "CONNECT_B3_ACTIVE_IND",
	[0x31] = "DISCONNECT_B3_IND",
	[0x33] = "DATA_B3_IND",
	[0x34] = "RESET_B3_IND",
	[0x35] = "CONNECT_B3_T90_ACTIVE_IND",
	[0x38] = "CONNECT_RESP",
	[0x39] = "CONNECT_ACTIVE_RESP",
	[0x3a] = "DISCONNECT_RESP",
	[0x3c] = "MANUFACTURER_IND",
	[0x3e] = "INFO_RESP",
	[0x3f] = "FACILITY_RESP",
	[0x41] = "CONNECT_B3_RESP",
	[0x42] = "CONNECT_B3_ACTIVE_RESP",
	[0x43] = "DISCONNECT_B3_RESP",
	[0x45] = "DATA_B3_RESP",
	[0x46] = "RESET_B3_RESP",
	[0x47] = "CONNECT_B3_T90_ACTIVE_RESP",
	[0x4e] = "MANUFACTURER_RESP"
पूर्ण;

/**
 * capi_cmd2str() - convert CAPI 2.0 command/subcommand number to name
 * @cmd:	command number
 * @subcmd:	subcommand number
 *
 * Return value: अटल string
 */

अक्षर *capi_cmd2str(u8 cmd, u8 subcmd)
अणु
	अक्षर *result;

	result = mnames[command_2_index(cmd, subcmd)];
	अगर (result == शून्य)
		result = "INVALID_COMMAND";
	वापस result;
पूर्ण


/*-------------------------------------------------------*/

#अगर_घोषित CONFIG_CAPI_TRACE

/*-------------------------------------------------------*/

अटल अक्षर *pnames[] =
अणु
	/*00 */ शून्य,
	/*01 */ शून्य,
	/*02 */ शून्य,
	/*03 */ "Controller/PLCI/NCCI",
	/*04 */ "AdditionalInfo",
	/*05 */ "B1configuration",
	/*06 */ "B1protocol",
	/*07 */ "B2configuration",
	/*08 */ "B2protocol",
	/*09 */ "B3configuration",
	/*0a */ "B3protocol",
	/*0b */ "BC",
	/*0c */ "BChannelinformation",
	/*0d */ "BProtocol",
	/*0e */ "CalledPartyNumber",
	/*0f */ "CalledPartySubaddress",
	/*10 */ "CallingPartyNumber",
	/*11 */ "CallingPartySubaddress",
	/*12 */ "CIPmask",
	/*13 */ "CIPmask2",
	/*14 */ "CIPValue",
	/*15 */ "Class",
	/*16 */ "ConnectedNumber",
	/*17 */ "ConnectedSubaddress",
	/*18 */ "Data32",
	/*19 */ "DataHandle",
	/*1a */ "DataLength",
	/*1b */ "FacilityConfirmationParameter",
	/*1c */ "Facilitydataarray",
	/*1d */ "FacilityIndicationParameter",
	/*1e */ "FacilityRequestParameter",
	/*1f */ "FacilitySelector",
	/*20 */ "Flags",
	/*21 */ "Function",
	/*22 */ "HLC",
	/*23 */ "Info",
	/*24 */ "InfoElement",
	/*25 */ "InfoMask",
	/*26 */ "InfoNumber",
	/*27 */ "Keypadfacility",
	/*28 */ "LLC",
	/*29 */ "ManuData",
	/*2a */ "ManuID",
	/*2b */ "NCPI",
	/*2c */ "Reason",
	/*2d */ "Reason_B3",
	/*2e */ "Reject",
	/*2f */ "Useruserdata"
पूर्ण;

#समावेश <मानकतर्क.स>

/*-------------------------------------------------------*/
अटल _cdebbuf *bufprपूर्णांक(_cdebbuf *cdb, अक्षर *fmt, ...)
अणु
	बहु_सूची f;
	माप_प्रकार n, r;

	अगर (!cdb)
		वापस शून्य;
	बहु_शुरू(f, fmt);
	r = cdb->size - cdb->pos;
	n = vsnम_लिखो(cdb->p, r, fmt, f);
	बहु_पूर्ण(f);
	अगर (n >= r) अणु
		/* truncated, need bigger buffer */
		माप_प्रकार ns = 2 * cdb->size;
		u_अक्षर *nb;

		जबतक ((ns - cdb->pos) <= n)
			ns *= 2;
		nb = kदो_स्मृति(ns, GFP_ATOMIC);
		अगर (!nb) अणु
			cdebbuf_मुक्त(cdb);
			वापस शून्य;
		पूर्ण
		स_नकल(nb, cdb->buf, cdb->pos);
		kमुक्त(cdb->buf);
		nb[cdb->pos] = 0;
		cdb->buf = nb;
		cdb->p = cdb->buf + cdb->pos;
		cdb->size = ns;
		बहु_शुरू(f, fmt);
		r = cdb->size - cdb->pos;
		n = vsnम_लिखो(cdb->p, r, fmt, f);
		बहु_पूर्ण(f);
	पूर्ण
	cdb->p += n;
	cdb->pos += n;
	वापस cdb;
पूर्ण

अटल _cdebbuf *prपूर्णांककाष्ठाlen(_cdebbuf *cdb, u8 *m, अचिन्हित len)
अणु
	अचिन्हित hex = 0;

	अगर (!cdb)
		वापस शून्य;
	क्रम (; len; len--, m++)
		अगर (है_अक्षर_अंक(*m) || *m == ' ') अणु
			अगर (hex)
				cdb = bufprपूर्णांक(cdb, ">");
			cdb = bufprपूर्णांक(cdb, "%c", *m);
			hex = 0;
		पूर्ण अन्यथा अणु
			अगर (!hex)
				cdb = bufprपूर्णांक(cdb, "<%02x", *m);
			अन्यथा
				cdb = bufprपूर्णांक(cdb, " %02x", *m);
			hex = 1;
		पूर्ण
	अगर (hex)
		cdb = bufprपूर्णांक(cdb, ">");
	वापस cdb;
पूर्ण

अटल _cdebbuf *prपूर्णांककाष्ठा(_cdebbuf *cdb, u8 *m)
अणु
	अचिन्हित len;

	अगर (m[0] != 0xff) अणु
		len = m[0];
		m += 1;
	पूर्ण अन्यथा अणु
		len = ((u16 *) (m + 1))[0];
		m += 3;
	पूर्ण
	cdb = prपूर्णांककाष्ठाlen(cdb, m, len);
	वापस cdb;
पूर्ण

/*-------------------------------------------------------*/
#घोषणा NAME (pnames[cmsg->par[cmsg->p]])

अटल _cdebbuf *protocol_message_2_pars(_cdebbuf *cdb, _cmsg *cmsg, पूर्णांक level)
अणु
	अगर (!cmsg->par)
		वापस शून्य;	/* invalid command/subcommand */

	क्रम (; TYP != _CEND; cmsg->p++) अणु
		पूर्णांक slen = 29 + 3 - level;
		पूर्णांक i;

		अगर (!cdb)
			वापस शून्य;
		cdb = bufprपूर्णांक(cdb, "  ");
		क्रम (i = 0; i < level - 1; i++)
			cdb = bufprपूर्णांक(cdb, " ");

		चयन (TYP) अणु
		हाल _CBYTE:
			cdb = bufprपूर्णांक(cdb, "%-*s = 0x%x\n", slen, NAME, *(u8 *) (cmsg->m + cmsg->l));
			cmsg->l++;
			अवरोध;
		हाल _CWORD:
			cdb = bufprपूर्णांक(cdb, "%-*s = 0x%x\n", slen, NAME, *(u16 *) (cmsg->m + cmsg->l));
			cmsg->l += 2;
			अवरोध;
		हाल _CDWORD:
			cdb = bufprपूर्णांक(cdb, "%-*s = 0x%lx\n", slen, NAME, *(u32 *) (cmsg->m + cmsg->l));
			cmsg->l += 4;
			अवरोध;
		हाल _CSTRUCT:
			cdb = bufprपूर्णांक(cdb, "%-*s = ", slen, NAME);
			अगर (cmsg->m[cmsg->l] == '\0')
				cdb = bufprपूर्णांक(cdb, "default");
			अन्यथा
				cdb = prपूर्णांककाष्ठा(cdb, cmsg->m + cmsg->l);
			cdb = bufprपूर्णांक(cdb, "\n");
			अगर (cmsg->m[cmsg->l] != 0xff)
				cmsg->l += 1 + cmsg->m[cmsg->l];
			अन्यथा
				cmsg->l += 3 + *(u16 *) (cmsg->m + cmsg->l + 1);

			अवरोध;

		हाल _CMSTRUCT:
/*----- Metastruktur 0 -----*/
			अगर (cmsg->m[cmsg->l] == '\0') अणु
				cdb = bufprपूर्णांक(cdb, "%-*s = default\n", slen, NAME);
				cmsg->l++;
				jumpcकाष्ठा(cmsg);
			पूर्ण अन्यथा अणु
				अक्षर *name = NAME;
				अचिन्हित _l = cmsg->l;
				cdb = bufprपूर्णांक(cdb, "%-*s\n", slen, name);
				cmsg->l = (cmsg->m + _l)[0] == 255 ? cmsg->l + 3 : cmsg->l + 1;
				cmsg->p++;
				cdb = protocol_message_2_pars(cdb, cmsg, level + 1);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	वापस cdb;
पूर्ण
/*-------------------------------------------------------*/

अटल _cdebbuf *g_debbuf;
अटल u_दीर्घ g_debbuf_lock;
अटल _cmsg *g_cmsg;

अटल _cdebbuf *cdebbuf_alloc(व्योम)
अणु
	_cdebbuf *cdb;

	अगर (likely(!test_and_set_bit(1, &g_debbuf_lock))) अणु
		cdb = g_debbuf;
		जाओ init;
	पूर्ण अन्यथा
		cdb = kदो_स्मृति(माप(_cdebbuf), GFP_ATOMIC);
	अगर (!cdb)
		वापस शून्य;
	cdb->buf = kदो_स्मृति(CDEBUG_SIZE, GFP_ATOMIC);
	अगर (!cdb->buf) अणु
		kमुक्त(cdb);
		वापस शून्य;
	पूर्ण
	cdb->size = CDEBUG_SIZE;
init:
	cdb->buf[0] = 0;
	cdb->p = cdb->buf;
	cdb->pos = 0;
	वापस cdb;
पूर्ण

/**
 * cdebbuf_मुक्त() - मुक्त CAPI debug buffer
 * @cdb:	buffer to मुक्त
 */

व्योम cdebbuf_मुक्त(_cdebbuf *cdb)
अणु
	अगर (likely(cdb == g_debbuf)) अणु
		test_and_clear_bit(1, &g_debbuf_lock);
		वापस;
	पूर्ण
	अगर (likely(cdb))
		kमुक्त(cdb->buf);
	kमुक्त(cdb);
पूर्ण


/**
 * capi_message2str() - क्रमmat CAPI 2.0 message क्रम prपूर्णांकing
 * @msg:	CAPI 2.0 message
 *
 * Allocates a CAPI debug buffer and fills it with a prपूर्णांकable representation
 * of the CAPI 2.0 message in @msg.
 * Return value: allocated debug buffer, शून्य on error
 * The वापसed buffer should be मुक्तd by a call to cdebbuf_मुक्त() after use.
 */

_cdebbuf *capi_message2str(u8 *msg)
अणु
	_cdebbuf *cdb;
	_cmsg	*cmsg;

	cdb = cdebbuf_alloc();
	अगर (unlikely(!cdb))
		वापस शून्य;
	अगर (likely(cdb == g_debbuf))
		cmsg = g_cmsg;
	अन्यथा
		cmsg = kदो_स्मृति(माप(_cmsg), GFP_ATOMIC);
	अगर (unlikely(!cmsg)) अणु
		cdebbuf_मुक्त(cdb);
		वापस शून्य;
	पूर्ण
	cmsg->m = msg;
	cmsg->l = 8;
	cmsg->p = 0;
	byteTRcpy(cmsg->m + 4, &cmsg->Command);
	byteTRcpy(cmsg->m + 5, &cmsg->Subcommand);
	cmsg->par = capi_cmd2par(cmsg->Command, cmsg->Subcommand);

	cdb = bufprपूर्णांक(cdb, "%-26s ID=%03d #0x%04x LEN=%04d\n",
		       capi_cmd2str(cmsg->Command, cmsg->Subcommand),
		       ((अचिन्हित लघु *) msg)[1],
		       ((अचिन्हित लघु *) msg)[3],
		       ((अचिन्हित लघु *) msg)[0]);

	cdb = protocol_message_2_pars(cdb, cmsg, 1);
	अगर (unlikely(cmsg != g_cmsg))
		kमुक्त(cmsg);
	वापस cdb;
पूर्ण

पूर्णांक __init cdebug_init(व्योम)
अणु
	g_cmsg = kदो_स्मृति(माप(_cmsg), GFP_KERNEL);
	अगर (!g_cmsg)
		वापस -ENOMEM;
	g_debbuf = kदो_स्मृति(माप(_cdebbuf), GFP_KERNEL);
	अगर (!g_debbuf) अणु
		kमुक्त(g_cmsg);
		वापस -ENOMEM;
	पूर्ण
	g_debbuf->buf = kदो_स्मृति(CDEBUG_GSIZE, GFP_KERNEL);
	अगर (!g_debbuf->buf) अणु
		kमुक्त(g_cmsg);
		kमुक्त(g_debbuf);
		वापस -ENOMEM;
	पूर्ण
	g_debbuf->size = CDEBUG_GSIZE;
	g_debbuf->buf[0] = 0;
	g_debbuf->p = g_debbuf->buf;
	g_debbuf->pos = 0;
	वापस 0;
पूर्ण

व्योम cdebug_निकास(व्योम)
अणु
	अगर (g_debbuf)
		kमुक्त(g_debbuf->buf);
	kमुक्त(g_debbuf);
	kमुक्त(g_cmsg);
पूर्ण

#अन्यथा /* !CONFIG_CAPI_TRACE */

अटल _cdebbuf g_debbuf = अणु"CONFIG_CAPI_TRACE not enabled", शून्य, 0, 0पूर्ण;

_cdebbuf *capi_message2str(u8 *msg)
अणु
	वापस &g_debbuf;
पूर्ण

_cdebbuf *capi_cmsg2str(_cmsg *cmsg)
अणु
	वापस &g_debbuf;
पूर्ण

व्योम cdebbuf_मुक्त(_cdebbuf *cdb)
अणु
पूर्ण

पूर्णांक __init cdebug_init(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम cdebug_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर
