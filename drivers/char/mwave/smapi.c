<शैली गुरु>
/*
*
* smapi.c -- SMAPI पूर्णांकerface routines
*
*
* Written By: Mike Sullivan IBM Corporation
*
* Copyright (C) 1999 IBM Corporation
*
* This program is मुक्त software; you can redistribute it and/or modअगरy
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License क्रम more details.
*
* NO WARRANTY
* THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT
* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,
* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is
* solely responsible क्रम determining the appropriateness of using and
* distributing the Program and assumes all risks associated with its
* exercise of rights under this Agreement, including but not limited to
* the risks and costs of program errors, damage to or loss of data,
* programs or equipment, and unavailability or पूर्णांकerruption of operations.
*
* DISCLAIMER OF LIABILITY
* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
* सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES
*
* You should have received a copy of the GNU General Public License
* aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*
* 10/23/2000 - Alpha Release
*	First release to the खुला
*/

#समावेश <linux/kernel.h>
#समावेश <linux/mc146818rtc.h>	/* CMOS defines */
#समावेश "smapi.h"
#समावेश "mwavedd.h"

अटल अचिन्हित लघु g_usSmapiPort = 0;


अटल पूर्णांक smapi_request(अचिन्हित लघु inBX, अचिन्हित लघु inCX,
			 अचिन्हित लघु inDI, अचिन्हित लघु inSI,
			 अचिन्हित लघु *outAX, अचिन्हित लघु *outBX,
			 अचिन्हित लघु *outCX, अचिन्हित लघु *outDX,
			 अचिन्हित लघु *outDI, अचिन्हित लघु *outSI)
अणु
	अचिन्हित लघु myoutAX = 2, *pmyoutAX = &myoutAX;
	अचिन्हित लघु myoutBX = 3, *pmyoutBX = &myoutBX;
	अचिन्हित लघु myoutCX = 4, *pmyoutCX = &myoutCX;
	अचिन्हित लघु myoutDX = 5, *pmyoutDX = &myoutDX;
	अचिन्हित लघु myoutDI = 6, *pmyoutDI = &myoutDI;
	अचिन्हित लघु myoutSI = 7, *pmyoutSI = &myoutSI;
	अचिन्हित लघु usSmapiOK = -EIO, *pusSmapiOK = &usSmapiOK;
	अचिन्हित पूर्णांक inBXCX = (inBX << 16) | inCX;
	अचिन्हित पूर्णांक inDISI = (inDI << 16) | inSI;
	पूर्णांक retval = 0;

	PRINTK_5(TRACE_SMAPI, "inBX %x inCX %x inDI %x inSI %x\n",
		inBX, inCX, inDI, inSI);

	__यंत्र__ __अस्थिर__("movw  $0x5380,%%ax\n\t"
			    "movl  %7,%%ebx\n\t"
			    "shrl  $16, %%ebx\n\t"
			    "movw  %7,%%cx\n\t"
			    "movl  %8,%%edi\n\t"
			    "shrl  $16,%%edi\n\t"
			    "movw  %8,%%si\n\t"
			    "movw  %9,%%dx\n\t"
			    "out   %%al,%%dx\n\t"
			    "out   %%al,$0x4F\n\t"
			    "cmpb  $0x53,%%ah\n\t"
			    "je    2f\n\t"
			    "1:\n\t"
			    "orb   %%ah,%%ah\n\t"
			    "jnz   2f\n\t"
			    "movw  %%ax,%0\n\t"
			    "movw  %%bx,%1\n\t"
			    "movw  %%cx,%2\n\t"
			    "movw  %%dx,%3\n\t"
			    "movw  %%di,%4\n\t"
			    "movw  %%si,%5\n\t"
			    "movw  $1,%6\n\t"
			    "2:\n\t":"=m"(*(अचिन्हित लघु *) pmyoutAX),
			    "=m"(*(अचिन्हित लघु *) pmyoutBX),
			    "=m"(*(अचिन्हित लघु *) pmyoutCX),
			    "=m"(*(अचिन्हित लघु *) pmyoutDX),
			    "=m"(*(अचिन्हित लघु *) pmyoutDI),
			    "=m"(*(अचिन्हित लघु *) pmyoutSI),
			    "=m"(*(अचिन्हित लघु *) pusSmapiOK)
			    :"m"(inBXCX), "m"(inDISI), "m"(g_usSmapiPort)
			    :"%eax", "%ebx", "%ecx", "%edx", "%edi",
			    "%esi");

	PRINTK_8(TRACE_SMAPI,
		"myoutAX %x myoutBX %x myoutCX %x myoutDX %x myoutDI %x myoutSI %x usSmapiOK %x\n",
		myoutAX, myoutBX, myoutCX, myoutDX, myoutDI, myoutSI,
		usSmapiOK);
	*outAX = myoutAX;
	*outBX = myoutBX;
	*outCX = myoutCX;
	*outDX = myoutDX;
	*outDI = myoutDI;
	*outSI = myoutSI;

	retval = (usSmapiOK == 1) ? 0 : -EIO;
	PRINTK_2(TRACE_SMAPI, "smapi::smapi_request exit retval %x\n", retval);
	वापस retval;
पूर्ण


पूर्णांक smapi_query_DSP_cfg(SMAPI_DSP_SETTINGS * pSettings)
अणु
	पूर्णांक bRC;
	अचिन्हित लघु usAX, usBX, usCX, usDX, usDI, usSI;
	अटल स्थिर अचिन्हित लघु ausDspBases[] = अणु
		0x0030, 0x4E30, 0x8E30, 0xCE30,
		0x0130, 0x0350, 0x0070, 0x0DB0 पूर्ण;
	अटल स्थिर अचिन्हित लघु ausUartBases[] = अणु
		0x03F8, 0x02F8, 0x03E8, 0x02E8 पूर्ण;

	PRINTK_1(TRACE_SMAPI, "smapi::smapi_query_DSP_cfg entry\n");

	bRC = smapi_request(0x1802, 0x0000, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) अणु
		PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_query_DSP_cfg: Error: Could not get DSP Settings. Aborting.\n");
		वापस bRC;
	पूर्ण

	PRINTK_1(TRACE_SMAPI, "smapi::smapi_query_DSP_cfg, smapi_request OK\n");

	pSettings->bDSPPresent = ((usBX & 0x0100) != 0);
	pSettings->bDSPEnabled = ((usCX & 0x0001) != 0);
	pSettings->usDspIRQ = usSI & 0x00FF;
	pSettings->usDspDMA = (usSI & 0xFF00) >> 8;
	अगर ((usDI & 0x00FF) < ARRAY_SIZE(ausDspBases)) अणु
		pSettings->usDspBaseIO = ausDspBases[usDI & 0x00FF];
	पूर्ण अन्यथा अणु
		pSettings->usDspBaseIO = 0;
	पूर्ण
	PRINTK_6(TRACE_SMAPI,
		"smapi::smapi_query_DSP_cfg get DSP Settings bDSPPresent %x bDSPEnabled %x usDspIRQ %x usDspDMA %x usDspBaseIO %x\n",
		pSettings->bDSPPresent, pSettings->bDSPEnabled,
		pSettings->usDspIRQ, pSettings->usDspDMA,
		pSettings->usDspBaseIO);

	/* check क्रम illegal values */
	अगर ( pSettings->usDspBaseIO == 0 ) 
		PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_query_DSP_cfg: Worry: DSP base I/O address is 0\n");
	अगर ( pSettings->usDspIRQ == 0 )
		PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_query_DSP_cfg: Worry: DSP IRQ line is 0\n");

	bRC = smapi_request(0x1804, 0x0000, 0, 0,
	   	&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) अणु
		PRINTK_ERROR("smapi::smapi_query_DSP_cfg: Error: Could not get DSP modem settings. Aborting.\n");
		वापस bRC;
	पूर्ण 

	PRINTK_1(TRACE_SMAPI, "smapi::smapi_query_DSP_cfg, smapi_request OK\n");

	pSettings->bModemEnabled = ((usCX & 0x0001) != 0);
	pSettings->usUartIRQ = usSI & 0x000F;
	अगर (((usSI & 0xFF00) >> 8) < ARRAY_SIZE(ausUartBases)) अणु
		pSettings->usUartBaseIO = ausUartBases[(usSI & 0xFF00) >> 8];
	पूर्ण अन्यथा अणु
		pSettings->usUartBaseIO = 0;
	पूर्ण

	PRINTK_4(TRACE_SMAPI,
		"smapi::smapi_query_DSP_cfg get DSP modem settings bModemEnabled %x usUartIRQ %x usUartBaseIO %x\n",
		pSettings->bModemEnabled,
		pSettings->usUartIRQ,
		pSettings->usUartBaseIO);

	/* check क्रम illegal values */
	अगर ( pSettings->usUartBaseIO == 0 ) 
		PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_query_DSP_cfg: Worry: UART base I/O address is 0\n");
	अगर ( pSettings->usUartIRQ == 0 )
		PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_query_DSP_cfg: Worry: UART IRQ line is 0\n");

	PRINTK_2(TRACE_SMAPI, "smapi::smapi_query_DSP_cfg exit bRC %x\n", bRC);

	वापस bRC;
पूर्ण


पूर्णांक smapi_set_DSP_cfg(व्योम)
अणु
	पूर्णांक bRC = -EIO;
	पूर्णांक i;
	अचिन्हित लघु usAX, usBX, usCX, usDX, usDI, usSI;
	अटल स्थिर अचिन्हित लघु ausDspBases[] = अणु
		0x0030, 0x4E30, 0x8E30, 0xCE30,
		0x0130, 0x0350, 0x0070, 0x0DB0 पूर्ण;
	अटल स्थिर अचिन्हित लघु ausUartBases[] = अणु
		0x03F8, 0x02F8, 0x03E8, 0x02E8 पूर्ण;
	अटल स्थिर अचिन्हित लघु ausDspIrqs[] = अणु
		5, 7, 10, 11, 15 पूर्ण;
	अटल स्थिर अचिन्हित लघु ausUartIrqs[] = अणु
		3, 4 पूर्ण;

	अचिन्हित लघु dspio_index = 0, uartio_index = 0;

	PRINTK_5(TRACE_SMAPI,
		"smapi::smapi_set_DSP_cfg entry mwave_3780i_irq %x mwave_3780i_io %x mwave_uart_irq %x mwave_uart_io %x\n",
		mwave_3780i_irq, mwave_3780i_io, mwave_uart_irq, mwave_uart_io);

	अगर (mwave_3780i_io) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ausDspBases); i++) अणु
			अगर (mwave_3780i_io == ausDspBases[i])
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(ausDspBases)) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_set_DSP_cfg: Error: Invalid mwave_3780i_io address %x. Aborting.\n", mwave_3780i_io);
			वापस bRC;
		पूर्ण
		dspio_index = i;
	पूर्ण

	अगर (mwave_3780i_irq) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ausDspIrqs); i++) अणु
			अगर (mwave_3780i_irq == ausDspIrqs[i])
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(ausDspIrqs)) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_set_DSP_cfg: Error: Invalid mwave_3780i_irq %x. Aborting.\n", mwave_3780i_irq);
			वापस bRC;
		पूर्ण
	पूर्ण

	अगर (mwave_uart_io) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ausUartBases); i++) अणु
			अगर (mwave_uart_io == ausUartBases[i])
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(ausUartBases)) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_set_DSP_cfg: Error: Invalid mwave_uart_io address %x. Aborting.\n", mwave_uart_io);
			वापस bRC;
		पूर्ण
		uartio_index = i;
	पूर्ण


	अगर (mwave_uart_irq) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ausUartIrqs); i++) अणु
			अगर (mwave_uart_irq == ausUartIrqs[i])
				अवरोध;
		पूर्ण
		अगर (i == ARRAY_SIZE(ausUartIrqs)) अणु
			PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_set_DSP_cfg: Error: Invalid mwave_uart_irq %x. Aborting.\n", mwave_uart_irq);
			वापस bRC;
		पूर्ण
	पूर्ण

	अगर (mwave_uart_irq || mwave_uart_io) अणु

		/* Check serial port A */
		bRC = smapi_request(0x1402, 0x0000, 0, 0,
			&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
		अगर (bRC) जाओ निकास_smapi_request_error;
		/* bRC == 0 */
		अगर (usBX & 0x0100) अणु	/* serial port A is present */
			अगर (usCX & 1) अणु	/* serial port is enabled */
				अगर ((usSI & 0xFF) == mwave_uart_irq) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_ERROR(KERN_ERR_MWAVE
						"smapi::smapi_set_DSP_cfg: Serial port A irq %x conflicts with mwave_uart_irq %x\n", usSI & 0xFF, mwave_uart_irq);
#अन्यथा
					PRINTK_3(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg: Serial port A irq %x conflicts with mwave_uart_irq %x\n", usSI & 0xFF, mwave_uart_irq);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_1(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg Disabling conflicting serial port\n");
					bRC = smapi_request(0x1403, 0x0100, 0, usSI,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
					bRC = smapi_request(0x1402, 0x0000, 0, 0,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
					जाओ निकास_conflict;
#पूर्ण_अगर
				पूर्ण अन्यथा अणु
					अगर ((usSI >> 8) == uartio_index) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
						PRINTK_ERROR(KERN_ERR_MWAVE
							"smapi::smapi_set_DSP_cfg: Serial port A base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI >> 8], ausUartBases[uartio_index]);
#अन्यथा
						PRINTK_3(TRACE_SMAPI,
							"smapi::smapi_set_DSP_cfg: Serial port A base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI >> 8], ausUartBases[uartio_index]);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
						PRINTK_1(TRACE_SMAPI,
							"smapi::smapi_set_DSP_cfg Disabling conflicting serial port A\n");
						bRC = smapi_request (0x1403, 0x0100, 0, usSI,
							&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
						अगर (bRC) जाओ निकास_smapi_request_error;
						bRC = smapi_request (0x1402, 0x0000, 0, 0,
							&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
						अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
						जाओ निकास_conflict;
#पूर्ण_अगर
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/* Check serial port B */
		bRC = smapi_request(0x1404, 0x0000, 0, 0,
			&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
		अगर (bRC) जाओ निकास_smapi_request_error;
		/* bRC == 0 */
		अगर (usBX & 0x0100) अणु	/* serial port B is present */
			अगर (usCX & 1) अणु	/* serial port is enabled */
				अगर ((usSI & 0xFF) == mwave_uart_irq) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_ERROR(KERN_ERR_MWAVE
						"smapi::smapi_set_DSP_cfg: Serial port B irq %x conflicts with mwave_uart_irq %x\n", usSI & 0xFF, mwave_uart_irq);
#अन्यथा
					PRINTK_3(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg: Serial port B irq %x conflicts with mwave_uart_irq %x\n", usSI & 0xFF, mwave_uart_irq);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_1(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg Disabling conflicting serial port B\n");
					bRC = smapi_request(0x1405, 0x0100, 0, usSI,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
					bRC = smapi_request(0x1404, 0x0000, 0, 0,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
					जाओ निकास_conflict;
#पूर्ण_अगर
				पूर्ण अन्यथा अणु
					अगर ((usSI >> 8) == uartio_index) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
						PRINTK_ERROR(KERN_ERR_MWAVE
							"smapi::smapi_set_DSP_cfg: Serial port B base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI >> 8], ausUartBases[uartio_index]);
#अन्यथा
						PRINTK_3(TRACE_SMAPI,
							"smapi::smapi_set_DSP_cfg: Serial port B base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI >> 8], ausUartBases[uartio_index]);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
						PRINTK_1 (TRACE_SMAPI,
						    "smapi::smapi_set_DSP_cfg Disabling conflicting serial port B\n");
						bRC = smapi_request (0x1405, 0x0100, 0, usSI,
							&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
						अगर (bRC) जाओ निकास_smapi_request_error;
						bRC = smapi_request (0x1404, 0x0000, 0, 0,
							&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
						अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
						जाओ निकास_conflict;
#पूर्ण_अगर
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		/* Check IR port */
		bRC = smapi_request(0x1700, 0x0000, 0, 0,
			&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
		अगर (bRC) जाओ निकास_smapi_request_error;
		bRC = smapi_request(0x1704, 0x0000, 0, 0,
			&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
		अगर (bRC) जाओ निकास_smapi_request_error;
		/* bRC == 0 */
		अगर ((usCX & 0xff) != 0xff) अणु /* IR port not disabled */
			अगर ((usCX & 0xff) == mwave_uart_irq) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
				PRINTK_ERROR(KERN_ERR_MWAVE
					"smapi::smapi_set_DSP_cfg: IR port irq %x conflicts with mwave_uart_irq %x\n", usCX & 0xff, mwave_uart_irq);
#अन्यथा
				PRINTK_3(TRACE_SMAPI,
					"smapi::smapi_set_DSP_cfg: IR port irq %x conflicts with mwave_uart_irq %x\n", usCX & 0xff, mwave_uart_irq);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
				PRINTK_1(TRACE_SMAPI,
					"smapi::smapi_set_DSP_cfg Disabling conflicting IR port\n");
				bRC = smapi_request(0x1701, 0x0100, 0, 0,
					&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
				अगर (bRC) जाओ निकास_smapi_request_error;
				bRC = smapi_request(0x1700, 0, 0, 0,
					&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
				अगर (bRC) जाओ निकास_smapi_request_error;
				bRC = smapi_request(0x1705, 0x01ff, 0, usSI,
					&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
				अगर (bRC) जाओ निकास_smapi_request_error;
				bRC = smapi_request(0x1704, 0x0000, 0, 0,
					&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
				अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
				जाओ निकास_conflict;
#पूर्ण_अगर
			पूर्ण अन्यथा अणु
				अगर ((usSI & 0xff) == uartio_index) अणु
#अगर_अघोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_ERROR(KERN_ERR_MWAVE
						"smapi::smapi_set_DSP_cfg: IR port base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI & 0xff], ausUartBases[uartio_index]);
#अन्यथा
					PRINTK_3(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg: IR port base I/O address %x conflicts with mwave uart I/O %x\n", ausUartBases[usSI & 0xff], ausUartBases[uartio_index]);
#पूर्ण_अगर
#अगर_घोषित MWAVE_FUTZ_WITH_OTHER_DEVICES
					PRINTK_1(TRACE_SMAPI,
						"smapi::smapi_set_DSP_cfg Disabling conflicting IR port\n");
					bRC = smapi_request(0x1701, 0x0100, 0, 0,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
					bRC = smapi_request(0x1700, 0, 0, 0,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
					bRC = smapi_request(0x1705, 0x01ff, 0, usSI,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
					bRC = smapi_request(0x1704, 0x0000, 0, 0,
						&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
					अगर (bRC) जाओ निकास_smapi_request_error;
#अन्यथा
					जाओ निकास_conflict;
#पूर्ण_अगर
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	bRC = smapi_request(0x1802, 0x0000, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

	अगर (mwave_3780i_io) अणु
		usDI = dspio_index;
	पूर्ण
	अगर (mwave_3780i_irq) अणु
		usSI = (usSI & 0xff00) | mwave_3780i_irq;
	पूर्ण

	bRC = smapi_request(0x1803, 0x0101, usDI, usSI,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

	bRC = smapi_request(0x1804, 0x0000, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

	अगर (mwave_uart_io) अणु
		usSI = (usSI & 0x00ff) | (uartio_index << 8);
	पूर्ण
	अगर (mwave_uart_irq) अणु
		usSI = (usSI & 0xff00) | mwave_uart_irq;
	पूर्ण
	bRC = smapi_request(0x1805, 0x0101, 0, usSI,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

	bRC = smapi_request(0x1802, 0x0000, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

	bRC = smapi_request(0x1804, 0x0000, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);
	अगर (bRC) जाओ निकास_smapi_request_error;

/* normal निकास: */
	PRINTK_1(TRACE_SMAPI, "smapi::smapi_set_DSP_cfg exit\n");
	वापस 0;

निकास_conflict:
	/* Message has alपढ़ोy been prपूर्णांकed */
	वापस -EIO;

निकास_smapi_request_error:
	PRINTK_ERROR(KERN_ERR_MWAVE "smapi::smapi_set_DSP_cfg exit on smapi_request error bRC %x\n", bRC);
	वापस bRC;
पूर्ण


पूर्णांक smapi_set_DSP_घातer_state(bool bOn)
अणु
	पूर्णांक bRC;
	अचिन्हित लघु usAX, usBX, usCX, usDX, usDI, usSI;
	अचिन्हित लघु usPowerFunction;

	PRINTK_2(TRACE_SMAPI, "smapi::smapi_set_DSP_power_state entry bOn %x\n", bOn);

	usPowerFunction = (bOn) ? 1 : 0;

	bRC = smapi_request(0x4901, 0x0000, 0, usPowerFunction,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);

	PRINTK_2(TRACE_SMAPI, "smapi::smapi_set_DSP_power_state exit bRC %x\n", bRC);

	वापस bRC;
पूर्ण

#अगर 0
अटल पूर्णांक SmapiQuerySystemID(व्योम)
अणु
	पूर्णांक bRC = -EIO;
	अचिन्हित लघु usAX = 0xffff, usBX = 0xffff, usCX = 0xffff,
		usDX = 0xffff, usDI = 0xffff, usSI = 0xffff;

	prपूर्णांकk("smapi::SmapiQUerySystemID entry\n");
	bRC = smapi_request(0x0000, 0, 0, 0,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);

	अगर (bRC == 0) अणु
		prपूर्णांकk("AX=%x, BX=%x, CX=%x, DX=%x, DI=%x, SI=%x\n",
			usAX, usBX, usCX, usDX, usDI, usSI);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("smapi::SmapiQuerySystemID smapi_request error\n");
	पूर्ण

	वापस bRC;
पूर्ण
#पूर्ण_अगर  /*  0  */

पूर्णांक smapi_init(व्योम)
अणु
	पूर्णांक retval = -EIO;
	अचिन्हित लघु usSmapiID = 0;
	अचिन्हित दीर्घ flags;

	PRINTK_1(TRACE_SMAPI, "smapi::smapi_init entry\n");

	spin_lock_irqsave(&rtc_lock, flags);
	usSmapiID = CMOS_READ(0x7C);
	usSmapiID |= (CMOS_READ(0x7D) << 8);
	spin_unlock_irqrestore(&rtc_lock, flags);
	PRINTK_2(TRACE_SMAPI, "smapi::smapi_init usSmapiID %x\n", usSmapiID);

	अगर (usSmapiID == 0x5349) अणु
		spin_lock_irqsave(&rtc_lock, flags);
		g_usSmapiPort = CMOS_READ(0x7E);
		g_usSmapiPort |= (CMOS_READ(0x7F) << 8);
		spin_unlock_irqrestore(&rtc_lock, flags);
		अगर (g_usSmapiPort == 0) अणु
			PRINTK_ERROR("smapi::smapi_init, ERROR unable to read from SMAPI port\n");
		पूर्ण अन्यथा अणु
			PRINTK_2(TRACE_SMAPI,
				"smapi::smapi_init, exit true g_usSmapiPort %x\n",
				g_usSmapiPort);
			retval = 0;
			//SmapiQuerySystemID();
		पूर्ण
	पूर्ण अन्यथा अणु
		PRINTK_ERROR("smapi::smapi_init, ERROR invalid usSmapiID\n");
		retval = -ENXIO;
	पूर्ण

	वापस retval;
पूर्ण
