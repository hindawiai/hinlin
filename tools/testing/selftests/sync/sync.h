<शैली गुरु>
/*
 *  sync असलtraction
 *  Copyright 2015-2016 Collabora Ltd.
 *
 *  Based on the implementation from the Android Open Source Project,
 *
 *  Copyright 2012 Google, Inc
 *
 *  Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 *  copy of this software and associated करोcumentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to करो so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित SELFTESTS_SYNC_H
#घोषणा SELFTESTS_SYNC_H

#घोषणा FENCE_STATUS_ERROR	(-1)
#घोषणा FENCE_STATUS_ACTIVE	(0)
#घोषणा FENCE_STATUS_SIGNALED	(1)

पूर्णांक sync_रुको(पूर्णांक fd, पूर्णांक समयout);
पूर्णांक sync_merge(स्थिर अक्षर *name, पूर्णांक fd1, पूर्णांक fd2);
पूर्णांक sync_fence_size(पूर्णांक fd);
पूर्णांक sync_fence_count_with_status(पूर्णांक fd, पूर्णांक status);

#पूर्ण_अगर
