<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा _GNU_SOURCE
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <sys/msg.h>
#समावेश <fcntl.h>

#समावेश "../kselftest.h"

#घोषणा MAX_MSG_SIZE		32

काष्ठा msg1 अणु
	पूर्णांक msize;
	दीर्घ mtype;
	अक्षर mtext[MAX_MSG_SIZE];
पूर्ण;

#घोषणा TEST_STRING "Test sysv5 msg"
#घोषणा MSG_TYPE 1

#घोषणा ANOTHER_TEST_STRING "Yet another test sysv5 msg"
#घोषणा ANOTHER_MSG_TYPE 26538

काष्ठा msgque_data अणु
	key_t key;
	पूर्णांक msq_id;
	पूर्णांक qbytes;
	पूर्णांक qnum;
	पूर्णांक mode;
	काष्ठा msg1 *messages;
पूर्ण;

पूर्णांक restore_queue(काष्ठा msgque_data *msgque)
अणु
	पूर्णांक fd, ret, id, i;
	अक्षर buf[32];

	fd = खोलो("/proc/sys/kernel/msg_next_id", O_WRONLY);
	अगर (fd == -1) अणु
		म_लिखो("Failed to open /proc/sys/kernel/msg_next_id\n");
		वापस -त्रुटि_सं;
	पूर्ण
	प्र_लिखो(buf, "%d", msgque->msq_id);

	ret = ग_लिखो(fd, buf, म_माप(buf));
	अगर (ret != म_माप(buf)) अणु
		म_लिखो("Failed to write to /proc/sys/kernel/msg_next_id\n");
		वापस -त्रुटि_सं;
	पूर्ण

	id = msgget(msgque->key, msgque->mode | IPC_CREAT | IPC_EXCL);
	अगर (id == -1) अणु
		म_लिखो("Failed to create queue\n");
		वापस -त्रुटि_सं;
	पूर्ण

	अगर (id != msgque->msq_id) अणु
		म_लिखो("Restored queue has wrong id (%d instead of %d)\n",
							id, msgque->msq_id);
		ret = -EFAULT;
		जाओ destroy;
	पूर्ण

	क्रम (i = 0; i < msgque->qnum; i++) अणु
		अगर (msgsnd(msgque->msq_id, &msgque->messages[i].mtype,
			   msgque->messages[i].msize, IPC_NOWAIT) != 0) अणु
			म_लिखो("msgsnd failed (%m)\n");
			ret = -त्रुटि_सं;
			जाओ destroy;
		पूर्ण
	पूर्ण
	वापस 0;

destroy:
	अगर (msgctl(id, IPC_RMID, शून्य))
		म_लिखो("Failed to destroy queue: %d\n", -त्रुटि_सं);
	वापस ret;
पूर्ण

पूर्णांक check_and_destroy_queue(काष्ठा msgque_data *msgque)
अणु
	काष्ठा msg1 message;
	पूर्णांक cnt = 0, ret;

	जबतक (1) अणु
		ret = msgrcv(msgque->msq_id, &message.mtype, MAX_MSG_SIZE,
				0, IPC_NOWAIT);
		अगर (ret < 0) अणु
			अगर (त्रुटि_सं == ENOMSG)
				अवरोध;
			म_लिखो("Failed to read IPC message: %m\n");
			ret = -त्रुटि_सं;
			जाओ err;
		पूर्ण
		अगर (ret != msgque->messages[cnt].msize) अणु
			म_लिखो("Wrong message size: %d (expected %d)\n", ret,
						msgque->messages[cnt].msize);
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अगर (message.mtype != msgque->messages[cnt].mtype) अणु
			म_लिखो("Wrong message type\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अगर (स_भेद(message.mtext, msgque->messages[cnt].mtext, ret)) अणु
			म_लिखो("Wrong message content\n");
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		cnt++;
	पूर्ण

	अगर (cnt != msgque->qnum) अणु
		म_लिखो("Wrong message number\n");
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = 0;
err:
	अगर (msgctl(msgque->msq_id, IPC_RMID, शून्य)) अणु
		म_लिखो("Failed to destroy queue: %d\n", -त्रुटि_सं);
		वापस -त्रुटि_सं;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक dump_queue(काष्ठा msgque_data *msgque)
अणु
	काष्ठा msqid_ds ds;
	पूर्णांक kern_id;
	पूर्णांक i, ret;

	क्रम (kern_id = 0; kern_id < 256; kern_id++) अणु
		ret = msgctl(kern_id, MSG_STAT, &ds);
		अगर (ret < 0) अणु
			अगर (त्रुटि_सं == EINVAL)
				जारी;
			म_लिखो("Failed to get stats for IPC queue with id %d\n",
					kern_id);
			वापस -त्रुटि_सं;
		पूर्ण

		अगर (ret == msgque->msq_id)
			अवरोध;
	पूर्ण

	msgque->messages = दो_स्मृति(माप(काष्ठा msg1) * ds.msg_qnum);
	अगर (msgque->messages == शून्य) अणु
		म_लिखो("Failed to get stats for IPC queue\n");
		वापस -ENOMEM;
	पूर्ण

	msgque->qnum = ds.msg_qnum;
	msgque->mode = ds.msg_perm.mode;
	msgque->qbytes = ds.msg_qbytes;

	क्रम (i = 0; i < msgque->qnum; i++) अणु
		ret = msgrcv(msgque->msq_id, &msgque->messages[i].mtype,
				MAX_MSG_SIZE, i, IPC_NOWAIT | MSG_COPY);
		अगर (ret < 0) अणु
			म_लिखो("Failed to copy IPC message: %m (%d)\n", त्रुटि_सं);
			वापस -त्रुटि_सं;
		पूर्ण
		msgque->messages[i].msize = ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fill_msgque(काष्ठा msgque_data *msgque)
अणु
	काष्ठा msg1 msgbuf;

	msgbuf.mtype = MSG_TYPE;
	स_नकल(msgbuf.mtext, TEST_STRING, माप(TEST_STRING));
	अगर (msgsnd(msgque->msq_id, &msgbuf.mtype, माप(TEST_STRING),
				IPC_NOWAIT) != 0) अणु
		म_लिखो("First message send failed (%m)\n");
		वापस -त्रुटि_सं;
	पूर्ण

	msgbuf.mtype = ANOTHER_MSG_TYPE;
	स_नकल(msgbuf.mtext, ANOTHER_TEST_STRING, माप(ANOTHER_TEST_STRING));
	अगर (msgsnd(msgque->msq_id, &msgbuf.mtype, माप(ANOTHER_TEST_STRING),
				IPC_NOWAIT) != 0) अणु
		म_लिखो("Second message send failed (%m)\n");
		वापस -त्रुटि_सं;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक msg, pid, err;
	काष्ठा msgque_data msgque;

	अगर (getuid() != 0)
		वापस ksft_निकास_skip(
				"Please run the test as root - Exiting.\n");

	msgque.key = ftok(argv[0], 822155650);
	अगर (msgque.key == -1) अणु
		म_लिखो("Can't make key: %d\n", -त्रुटि_सं);
		वापस ksft_निकास_fail();
	पूर्ण

	msgque.msq_id = msgget(msgque.key, IPC_CREAT | IPC_EXCL | 0666);
	अगर (msgque.msq_id == -1) अणु
		err = -त्रुटि_सं;
		म_लिखो("Can't create queue: %d\n", err);
		जाओ err_out;
	पूर्ण

	err = fill_msgque(&msgque);
	अगर (err) अणु
		म_लिखो("Failed to fill queue: %d\n", err);
		जाओ err_destroy;
	पूर्ण

	err = dump_queue(&msgque);
	अगर (err) अणु
		म_लिखो("Failed to dump queue: %d\n", err);
		जाओ err_destroy;
	पूर्ण

	err = check_and_destroy_queue(&msgque);
	अगर (err) अणु
		म_लिखो("Failed to check and destroy queue: %d\n", err);
		जाओ err_out;
	पूर्ण

	err = restore_queue(&msgque);
	अगर (err) अणु
		म_लिखो("Failed to restore queue: %d\n", err);
		जाओ err_destroy;
	पूर्ण

	err = check_and_destroy_queue(&msgque);
	अगर (err) अणु
		म_लिखो("Failed to test queue: %d\n", err);
		जाओ err_out;
	पूर्ण
	वापस ksft_निकास_pass();

err_destroy:
	अगर (msgctl(msgque.msq_id, IPC_RMID, शून्य)) अणु
		म_लिखो("Failed to destroy queue: %d\n", -त्रुटि_सं);
		वापस ksft_निकास_fail();
	पूर्ण
err_out:
	वापस ksft_निकास_fail();
पूर्ण
