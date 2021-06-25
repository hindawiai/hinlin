<शैली गुरु>
/*
 *  sw_sync असलtraction
 *
 *  Copyright 2015-2016 Collabora Ltd.
 *
 *  Based on the implementation from the Android Open Source Project,
 *
 *  Copyright 2013 Google, Inc
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

#अगर_अघोषित SELFTESTS_SW_SYNC_H
#घोषणा SELFTESTS_SW_SYNC_H

/*
 * sw_sync is मुख्यly पूर्णांकended क्रम testing and should not be compiled पूर्णांकo
 * production kernels
 */

पूर्णांक sw_sync_समयline_create(व्योम);
पूर्णांक sw_sync_समयline_is_valid(पूर्णांक fd);
पूर्णांक sw_sync_समयline_inc(पूर्णांक fd, अचिन्हित पूर्णांक count);
व्योम sw_sync_समयline_destroy(पूर्णांक fd);

पूर्णांक sw_sync_fence_create(पूर्णांक fd, स्थिर अक्षर *name, अचिन्हित पूर्णांक value);
पूर्णांक sw_sync_fence_is_valid(पूर्णांक fd);
व्योम sw_sync_fence_destroy(पूर्णांक fd);

#पूर्ण_अगर
