<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  Syslog पूर्णांकernals
 *
 *  Copyright 2010 Canonical, Ltd.
 *  Author: Kees Cook <kees.cook@canonical.com>
 */

#अगर_अघोषित _LINUX_SYSLOG_H
#घोषणा _LINUX_SYSLOG_H

/* Close the log.  Currently a NOP. */
#घोषणा SYSLOG_ACTION_CLOSE          0
/* Open the log. Currently a NOP. */
#घोषणा SYSLOG_ACTION_OPEN           1
/* Read from the log. */
#घोषणा SYSLOG_ACTION_READ           2
/* Read all messages reमुख्यing in the ring buffer. */
#घोषणा SYSLOG_ACTION_READ_ALL       3
/* Read and clear all messages reमुख्यing in the ring buffer */
#घोषणा SYSLOG_ACTION_READ_CLEAR     4
/* Clear ring buffer. */
#घोषणा SYSLOG_ACTION_CLEAR          5
/* Disable prपूर्णांकk's to console */
#घोषणा SYSLOG_ACTION_CONSOLE_OFF    6
/* Enable prपूर्णांकk's to console */
#घोषणा SYSLOG_ACTION_CONSOLE_ON     7
/* Set level of messages prपूर्णांकed to console */
#घोषणा SYSLOG_ACTION_CONSOLE_LEVEL  8
/* Return number of unपढ़ो अक्षरacters in the log buffer */
#घोषणा SYSLOG_ACTION_SIZE_UNREAD    9
/* Return size of the log buffer */
#घोषणा SYSLOG_ACTION_SIZE_BUFFER   10

#घोषणा SYSLOG_FROM_READER           0
#घोषणा SYSLOG_FROM_PROC             1

पूर्णांक करो_syslog(पूर्णांक type, अक्षर __user *buf, पूर्णांक count, पूर्णांक source);

#पूर्ण_अगर /* _LINUX_SYSLOG_H */
