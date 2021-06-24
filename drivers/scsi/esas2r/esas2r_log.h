<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_log.h
 *      For use with ATTO ExpressSAS R6xx SAS/SATA RAID controllers
 *
 *  Copyright (c) 2001-2013 ATTO Technology, Inc.
 *  (mailto:linuxdrivers@attotech.com)
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
 * Foundation, Inc., 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301,
 * USA.
 */

#अगर_अघोषित __esas2r_log_h__
#घोषणा __esas2r_log_h__

काष्ठा device;

क्रमागत अणु
	ESAS2R_LOG_NONE = 0,    /* no events logged */
	ESAS2R_LOG_CRIT = 1,    /* critical events  */
	ESAS2R_LOG_WARN = 2,    /* warning events   */
	ESAS2R_LOG_INFO = 3,    /* info events      */
	ESAS2R_LOG_DEBG = 4,    /* debugging events */
	ESAS2R_LOG_TRCE = 5,    /* tracing events   */

#अगर_घोषित ESAS2R_TRACE
	ESAS2R_LOG_DFLT = ESAS2R_LOG_TRCE
#अन्यथा
	ESAS2R_LOG_DFLT = ESAS2R_LOG_WARN
#पूर्ण_अगर
पूर्ण;

__म_लिखो(2, 3) पूर्णांक esas2r_log(स्थिर दीर्घ level, स्थिर अक्षर *क्रमmat, ...);
__म_लिखो(3, 4) पूर्णांक esas2r_log_dev(स्थिर दीर्घ level,
		   स्थिर काष्ठा device *dev,
		   स्थिर अक्षर *क्रमmat,
		   ...);
पूर्णांक esas2r_log_hexdump(स्थिर दीर्घ level,
		       स्थिर व्योम *buf,
		       माप_प्रकार len);

/*
 * the following macros are provided specअगरically क्रम debugging and tracing
 * messages.  esas2r_debug() is provided क्रम generic non-hardware layer
 * debugging and tracing events.  esas2r_hdebug is provided specअगरically क्रम
 * hardware layer debugging and tracing events.
 */

#अगर_घोषित ESAS2R_DEBUG
#घोषणा esas2r_debug(f, args ...) esas2r_log(ESAS2R_LOG_DEBG, f, ## args)
#घोषणा esas2r_hdebug(f, args ...) esas2r_log(ESAS2R_LOG_DEBG, f, ## args)
#अन्यथा
#घोषणा esas2r_debug(f, args ...)
#घोषणा esas2r_hdebug(f, args ...)
#पूर्ण_अगर  /* ESAS2R_DEBUG */

/*
 * the following macros are provided in order to trace the driver and catch
 * some more serious bugs.  be warned, enabling these macros may *severely*
 * impact perक्रमmance.
 */

#अगर_घोषित ESAS2R_TRACE
#घोषणा esas2r_bugon() \
	करो अणु \
		esas2r_log(ESAS2R_LOG_TRCE, "esas2r_bugon() called in %s:%d" \
			   " - dumping stack and stopping kernel", __func__, \
			   __LINE__); \
		dump_stack(); \
		BUG(); \
	पूर्ण जबतक (0)

#घोषणा esas2r_trace_enter() esas2r_log(ESAS2R_LOG_TRCE, "entered %s (%s:%d)", \
					__func__, __खाता__, __LINE__)
#घोषणा esas2r_trace_निकास() esas2r_log(ESAS2R_LOG_TRCE, "exited %s (%s:%d)", \
				       __func__, __खाता__, __LINE__)
#घोषणा esas2r_trace(f, args ...) esas2r_log(ESAS2R_LOG_TRCE, "(%s:%s:%d): " \
					     f, __func__, __खाता__, __LINE__, \
					     ## args)
#अन्यथा
#घोषणा esas2r_bugon()
#घोषणा esas2r_trace_enter()
#घोषणा esas2r_trace_निकास()
#घोषणा esas2r_trace(f, args ...)
#पूर्ण_अगर  /* ESAS2R_TRACE */

#पूर्ण_अगर  /* __esas2r_log_h__ */
