<शैली गुरु>
/*
*
* smapi.h -- declarations क्रम SMAPI पूर्णांकerface routines
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

#अगर_अघोषित _LINUX_SMAPI_H
#घोषणा _LINUX_SMAPI_H

प्रकार काष्ठा अणु
	पूर्णांक bDSPPresent;
	पूर्णांक bDSPEnabled;
	पूर्णांक bModemEnabled;
	पूर्णांक bMIDIEnabled;
	पूर्णांक bSblstEnabled;
	अचिन्हित लघु usDspIRQ;
	अचिन्हित लघु usDspDMA;
	अचिन्हित लघु usDspBaseIO;
	अचिन्हित लघु usUartIRQ;
	अचिन्हित लघु usUartBaseIO;
	अचिन्हित लघु usMidiIRQ;
	अचिन्हित लघु usMidiBaseIO;
	अचिन्हित लघु usSndblstIRQ;
	अचिन्हित लघु usSndblstDMA;
	अचिन्हित लघु usSndblstBaseIO;
पूर्ण SMAPI_DSP_SETTINGS;

पूर्णांक smapi_init(व्योम);
पूर्णांक smapi_query_DSP_cfg(SMAPI_DSP_SETTINGS * pSettings);
पूर्णांक smapi_set_DSP_cfg(व्योम);
पूर्णांक smapi_set_DSP_घातer_state(bool bOn);


#पूर्ण_अगर
