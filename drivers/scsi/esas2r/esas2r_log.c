<शैली गुरु>
/*
 *  linux/drivers/scsi/esas2r/esas2r_log.c
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

#समावेश "esas2r.h"

/*
 * this module within the driver is tasked with providing logging functionality.
 * the event_log_level module parameter controls the level of messages that are
 * written to the प्रणाली log.  the शेष level of messages that are written
 * are critical and warning messages.  अगर other types of messages are desired,
 * one simply needs to load the module with the correct value क्रम the
 * event_log_level module parameter.  क्रम example:
 *
 * insmod <module> event_log_level=1
 *
 * will load the module and only critical events will be written by this module
 * to the प्रणाली log.  अगर critical, warning, and inक्रमmation-level messages are
 * desired, the correct value क्रम the event_log_level module parameter
 * would be as follows:
 *
 * insmod <module> event_log_level=3
 */

#घोषणा EVENT_LOG_BUFF_SIZE 1024

अटल दीर्घ event_log_level = ESAS2R_LOG_DFLT;

module_param(event_log_level, दीर्घ, S_IRUGO | S_IRUSR);
MODULE_PARM_DESC(event_log_level,
		 "Specifies the level of events to report to the system log.  Critical and warning level events are logged by default.");

/* A shared buffer to use क्रम क्रमmatting messages. */
अटल अक्षर event_buffer[EVENT_LOG_BUFF_SIZE];

/* A lock to protect the shared buffer used क्रम क्रमmatting messages. */
अटल DEFINE_SPINLOCK(event_buffer_lock);

/*
 * translates an esas2r-defined logging event level to a kernel logging level.
 *
 * @param [in] level the esas2r-defined logging event level to translate
 *
 * @वापस the corresponding kernel logging level.
 */
अटल स्थिर अक्षर *translate_esas2r_event_level_to_kernel(स्थिर दीर्घ level)
अणु
	चयन (level) अणु
	हाल ESAS2R_LOG_CRIT:
		वापस KERN_CRIT;

	हाल ESAS2R_LOG_WARN:
		वापस KERN_WARNING;

	हाल ESAS2R_LOG_INFO:
		वापस KERN_INFO;

	हाल ESAS2R_LOG_DEBG:
	हाल ESAS2R_LOG_TRCE:
	शेष:
		वापस KERN_DEBUG;
	पूर्ण
पूर्ण

#आशय GCC diagnostic push
#अगर_अघोषित __clang__
#आशय GCC diagnostic ignored "-Wsuggest-attribute=format"
#पूर्ण_अगर

/*
 * the master logging function.  this function will क्रमmat the message as
 * outlined by the क्रमmatting string, the input device inक्रमmation and the
 * substitution arguments and output the resulting string to the प्रणाली log.
 *
 * @param [in] level  the event log level of the message
 * @param [in] dev    the device inक्रमmation
 * @param [in] क्रमmat the क्रमmatting string क्रम the message
 * @param [in] args   the substition arguments to the क्रमmatting string
 *
 * @वापस 0 on success, or -1 अगर an error occurred.
 */
अटल पूर्णांक esas2r_log_master(स्थिर दीर्घ level,
			     स्थिर काष्ठा device *dev,
			     स्थिर अक्षर *क्रमmat,
			     बहु_सूची args)
अणु
	अगर (level <= event_log_level) अणु
		अचिन्हित दीर्घ flags = 0;
		पूर्णांक retval = 0;
		अक्षर *buffer = event_buffer;
		माप_प्रकार buflen = EVENT_LOG_BUFF_SIZE;
		स्थिर अक्षर *fmt_nodev = "%s%s: ";
		स्थिर अक्षर *fmt_dev = "%s%s [%s, %s, %s]";
		स्थिर अक्षर *slevel =
			translate_esas2r_event_level_to_kernel(level);

		spin_lock_irqsave(&event_buffer_lock, flags);

		स_रखो(buffer, 0, buflen);

		/*
		 * क्रमmat the level onto the beginning of the string and करो
		 * some poपूर्णांकer arithmetic to move the poपूर्णांकer to the poपूर्णांक
		 * where the actual message can be inserted.
		 */

		अगर (dev == शून्य) अणु
			snम_लिखो(buffer, buflen, fmt_nodev, slevel,
				 ESAS2R_DRVR_NAME);
		पूर्ण अन्यथा अणु
			snम_लिखो(buffer, buflen, fmt_dev, slevel,
				 ESAS2R_DRVR_NAME,
				 (dev->driver ? dev->driver->name : "unknown"),
				 (dev->bus ? dev->bus->name : "unknown"),
				 dev_name(dev));
		पूर्ण

		buffer += म_माप(event_buffer);
		buflen -= म_माप(event_buffer);

		retval = vsnम_लिखो(buffer, buflen, क्रमmat, args);
		अगर (retval < 0) अणु
			spin_unlock_irqrestore(&event_buffer_lock, flags);
			वापस -1;
		पूर्ण

		/*
		 * Put a line अवरोध at the end of the क्रमmatted string so that
		 * we करोn't wind up with run-on messages.
		 */
		prपूर्णांकk("%s\n", event_buffer);

		spin_unlock_irqrestore(&event_buffer_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

#आशय GCC diagnostic pop

/*
 * क्रमmats and logs a message to the प्रणाली log.
 *
 * @param [in] level  the event level of the message
 * @param [in] क्रमmat the क्रमmating string क्रम the message
 * @param [in] ...    the substitution arguments to the क्रमmatting string
 *
 * @वापस 0 on success, or -1 अगर an error occurred.
 */
पूर्णांक esas2r_log(स्थिर दीर्घ level, स्थिर अक्षर *क्रमmat, ...)
अणु
	पूर्णांक retval = 0;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	retval = esas2r_log_master(level, शून्य, क्रमmat, args);

	बहु_पूर्ण(args);

	वापस retval;
पूर्ण

/*
 * क्रमmats and logs a message to the प्रणाली log.  this message will include
 * device inक्रमmation.
 *
 * @param [in] level   the event level of the message
 * @param [in] dev     the device inक्रमmation
 * @param [in] क्रमmat  the क्रमmatting string क्रम the message
 * @param [in] ...     the substitution arguments to the क्रमmatting string
 *
 * @वापस 0 on success, or -1 अगर an error occurred.
 */
पूर्णांक esas2r_log_dev(स्थिर दीर्घ level,
		   स्थिर काष्ठा device *dev,
		   स्थिर अक्षर *क्रमmat,
		   ...)
अणु
	पूर्णांक retval = 0;
	बहु_सूची args;

	बहु_शुरू(args, क्रमmat);

	retval = esas2r_log_master(level, dev, क्रमmat, args);

	बहु_पूर्ण(args);

	वापस retval;
पूर्ण

/*
 * क्रमmats and logs a message to the प्रणाली log.  this message will include
 * device inक्रमmation.
 *
 * @param [in] level   the event level of the message
 * @param [in] buf
 * @param [in] len
 *
 * @वापस 0 on success, or -1 अगर an error occurred.
 */
पूर्णांक esas2r_log_hexdump(स्थिर दीर्घ level,
		       स्थिर व्योम *buf,
		       माप_प्रकार len)
अणु
	अगर (level <= event_log_level) अणु
		prपूर्णांक_hex_dump(translate_esas2r_event_level_to_kernel(level),
			       "", DUMP_PREFIX_OFFSET, 16, 1, buf,
			       len, true);
	पूर्ण

	वापस 1;
पूर्ण
