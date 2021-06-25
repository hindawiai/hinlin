<शैली गुरु>
/*
 * Logging Support क्रम MPT (Message Passing Technology) based controllers
 *
 * This code is based on drivers/scsi/mpt3sas/mpt3sas_debug.c
 * Copyright (C) 2012-2014  LSI Corporation
 * Copyright (C) 2013-2014 Avago Technologies
 *  (mailto: MPT-FusionLinux.pdl@avagotech.com)
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
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

 * DISCLAIMER OF LIABILITY
 * NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED
 * HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#अगर_अघोषित MPT3SAS_DEBUG_H_INCLUDED
#घोषणा MPT3SAS_DEBUG_H_INCLUDED

#घोषणा MPT_DEBUG			0x00000001
#घोषणा MPT_DEBUG_MSG_FRAME		0x00000002
#घोषणा MPT_DEBUG_SG			0x00000004
#घोषणा MPT_DEBUG_EVENTS		0x00000008
#घोषणा MPT_DEBUG_EVENT_WORK_TASK	0x00000010
#घोषणा MPT_DEBUG_INIT			0x00000020
#घोषणा MPT_DEBUG_EXIT			0x00000040
#घोषणा MPT_DEBUG_FAIL			0x00000080
#घोषणा MPT_DEBUG_TM			0x00000100
#घोषणा MPT_DEBUG_REPLY		0x00000200
#घोषणा MPT_DEBUG_HANDSHAKE		0x00000400
#घोषणा MPT_DEBUG_CONFIG		0x00000800
#घोषणा MPT_DEBUG_DL			0x00001000
#घोषणा MPT_DEBUG_RESET		0x00002000
#घोषणा MPT_DEBUG_SCSI			0x00004000
#घोषणा MPT_DEBUG_IOCTL		0x00008000
#घोषणा MPT_DEBUG_SAS			0x00020000
#घोषणा MPT_DEBUG_TRANSPORT		0x00040000
#घोषणा MPT_DEBUG_TASK_SET_FULL	0x00080000

#घोषणा MPT_DEBUG_TRIGGER_DIAG		0x00200000


#घोषणा MPT_CHECK_LOGGING(IOC, CMD, BITS)			\
अणु								\
	अगर (IOC->logging_level & BITS)				\
		CMD;						\
पूर्ण

/*
 * debug macros
 */

#घोषणा dprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG)

#घोषणा dsgprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SG)

#घोषणा devtprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_EVENTS)

#घोषणा dewtprपूर्णांकk(IOC, CMD)		\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_EVENT_WORK_TASK)

#घोषणा dinitprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_INIT)

#घोषणा dनिकासprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_EXIT)

#घोषणा dfailprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_FAIL)

#घोषणा dपंचांगprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_TM)

#घोषणा dreplyprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_REPLY)

#घोषणा dhsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_HANDSHAKE)

#घोषणा dcprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_CONFIG)

#घोषणा ddlprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_DL)

#घोषणा drsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_RESET)

#घोषणा dsprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SCSI)

#घोषणा dctlprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_IOCTL)

#घोषणा dsasprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SAS)

#घोषणा dsastransport(IOC, CMD)		\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_SAS_WIDE)

#घोषणा dmfprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_MSG_FRAME)

#घोषणा dtsfprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_TASK_SET_FULL)

#घोषणा dtransportprपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_TRANSPORT)

#घोषणा dTriggerDiagPrपूर्णांकk(IOC, CMD)			\
	MPT_CHECK_LOGGING(IOC, CMD, MPT_DEBUG_TRIGGER_DIAG)



/* अंतरभूत functions क्रम dumping debug data*/

/**
 * _debug_dump_mf - prपूर्णांक message frame contents
 * @mpi_request: poपूर्णांकer to message frame
 * @sz: number of dwords
 */
अटल अंतरभूत व्योम
_debug_dump_mf(व्योम *mpi_request, पूर्णांक sz)
अणु
	पूर्णांक i;
	__le32 *mfp = (__le32 *)mpi_request;

	pr_info("mf:\n\t");
	क्रम (i = 0; i < sz; i++) अणु
		अगर (i && ((i % 8) == 0))
			pr_info("\n\t");
		pr_info("%08x ", le32_to_cpu(mfp[i]));
	पूर्ण
	pr_info("\n");
पूर्ण
/**
 * _debug_dump_reply - prपूर्णांक message frame contents
 * @mpi_request: poपूर्णांकer to message frame
 * @sz: number of dwords
 */
अटल अंतरभूत व्योम
_debug_dump_reply(व्योम *mpi_request, पूर्णांक sz)
अणु
	पूर्णांक i;
	__le32 *mfp = (__le32 *)mpi_request;

	pr_info("reply:\n\t");
	क्रम (i = 0; i < sz; i++) अणु
		अगर (i && ((i % 8) == 0))
			pr_info("\n\t");
		pr_info("%08x ", le32_to_cpu(mfp[i]));
	पूर्ण
	pr_info("\n");
पूर्ण
/**
 * _debug_dump_config - prपूर्णांक config page contents
 * @mpi_request: poपूर्णांकer to message frame
 * @sz: number of dwords
 */
अटल अंतरभूत व्योम
_debug_dump_config(व्योम *mpi_request, पूर्णांक sz)
अणु
	पूर्णांक i;
	__le32 *mfp = (__le32 *)mpi_request;

	pr_info("config:\n\t");
	क्रम (i = 0; i < sz; i++) अणु
		अगर (i && ((i % 8) == 0))
			pr_info("\n\t");
		pr_info("%08x ", le32_to_cpu(mfp[i]));
	पूर्ण
	pr_info("\n");
पूर्ण

#पूर्ण_अगर /* MPT3SAS_DEBUG_H_INCLUDED */
