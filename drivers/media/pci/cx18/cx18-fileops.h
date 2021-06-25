<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 file operation functions
 *
 *  Derived from ivtv-fileops.h
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 */

/* Testing/Debugging */
पूर्णांक cx18_v4l2_खोलो(काष्ठा file *filp);
sमाप_प्रकार cx18_v4l2_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार count,
		      loff_t *pos);
sमाप_प्रकार cx18_v4l2_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार count,
		       loff_t *pos);
पूर्णांक cx18_v4l2_बंद(काष्ठा file *filp);
__poll_t cx18_v4l2_enc_poll(काष्ठा file *filp, poll_table *रुको);
पूर्णांक cx18_start_capture(काष्ठा cx18_खोलो_id *id);
व्योम cx18_stop_capture(काष्ठा cx18_खोलो_id *id, पूर्णांक gop_end);
व्योम cx18_mute(काष्ठा cx18 *cx);
व्योम cx18_unmute(काष्ठा cx18 *cx);
पूर्णांक cx18_v4l2_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma);
व्योम cx18_vb_समयout(काष्ठा समयr_list *t);

/* Shared with cx18-alsa module */
पूर्णांक cx18_claim_stream(काष्ठा cx18_खोलो_id *id, पूर्णांक type);
व्योम cx18_release_stream(काष्ठा cx18_stream *s);
