<शैली गुरु>
/*******************************************************************************
    Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.

    Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
    copy of this software and associated करोcumentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to करो so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

*******************************************************************************/
#अगर_अघोषित _cl006c_h_
#घोषणा _cl006c_h_

/* fields and values */
#घोषणा NV06C_PUT                                                  (0x00000040)
#घोषणा NV06C_PUT_PTR                                              31:2
#घोषणा NV06C_GET                                                  (0x00000044)
#घोषणा NV06C_GET_PTR                                              31:2

/* dma method descriptor क्रमmat */
#घोषणा NV06C_METHOD_ADDRESS                                       12:2
#घोषणा NV06C_METHOD_SUBCHANNEL                                    15:13
#घोषणा NV06C_METHOD_COUNT                                         28:18
#घोषणा NV06C_OPCODE                                               31:29
#घोषणा NV06C_OPCODE_METHOD                                        (0x00000000)
#घोषणा NV06C_OPCODE_NONINC_METHOD                                 (0x00000002)

/* dma data क्रमmat */
#घोषणा NV06C_DATA                                                 31:0

/* dma jump क्रमmat */
#घोषणा NV06C_OPCODE_JUMP                                          (0x00000001)
#घोषणा NV06C_JUMP_OFFSET                                          28:2
#पूर्ण_अगर /* _cl006c_h_ */
