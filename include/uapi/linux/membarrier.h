<शैली गुरु>
#अगर_अघोषित _UAPI_LINUX_MEMBARRIER_H
#घोषणा _UAPI_LINUX_MEMBARRIER_H

/*
 * linux/membarrier.h
 *
 * membarrier प्रणाली call API
 *
 * Copyright (c) 2010, 2015 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * क्रमागत membarrier_cmd - membarrier प्रणाली call command
 * @MEMBARRIER_CMD_QUERY:   Query the set of supported commands. It वापसs
 *                          a biपंचांगask of valid commands.
 * @MEMBARRIER_CMD_GLOBAL:  Execute a memory barrier on all running thपढ़ोs.
 *                          Upon वापस from प्रणाली call, the caller thपढ़ो
 *                          is ensured that all running thपढ़ोs have passed
 *                          through a state where all memory accesses to
 *                          user-space addresses match program order between
 *                          entry to and वापस from the प्रणाली call
 *                          (non-running thपढ़ोs are de facto in such a
 *                          state). This covers thपढ़ोs from all processes
 *                          running on the प्रणाली. This command वापसs 0.
 * @MEMBARRIER_CMD_GLOBAL_EXPEDITED:
 *                          Execute a memory barrier on all running thपढ़ोs
 *                          of all processes which previously रेजिस्टरed
 *                          with MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED.
 *                          Upon वापस from प्रणाली call, the caller thपढ़ो
 *                          is ensured that all running thपढ़ोs have passed
 *                          through a state where all memory accesses to
 *                          user-space addresses match program order between
 *                          entry to and वापस from the प्रणाली call
 *                          (non-running thपढ़ोs are de facto in such a
 *                          state). This only covers thपढ़ोs from processes
 *                          which रेजिस्टरed with
 *                          MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED.
 *                          This command वापसs 0. Given that
 *                          registration is about the पूर्णांकent to receive
 *                          the barriers, it is valid to invoke
 *                          MEMBARRIER_CMD_GLOBAL_EXPEDITED from a
 *                          non-रेजिस्टरed process.
 * @MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED:
 *                          Register the process पूर्णांकent to receive
 *                          MEMBARRIER_CMD_GLOBAL_EXPEDITED memory
 *                          barriers. Always वापसs 0.
 * @MEMBARRIER_CMD_PRIVATE_EXPEDITED:
 *                          Execute a memory barrier on each running
 *                          thपढ़ो beदीर्घing to the same process as the current
 *                          thपढ़ो. Upon वापस from प्रणाली call, the
 *                          caller thपढ़ो is ensured that all its running
 *                          thपढ़ोs siblings have passed through a state
 *                          where all memory accesses to user-space
 *                          addresses match program order between entry
 *                          to and वापस from the प्रणाली call
 *                          (non-running thपढ़ोs are de facto in such a
 *                          state). This only covers thपढ़ोs from the
 *                          same process as the caller thपढ़ो. This
 *                          command वापसs 0 on success. The
 *                          "expedited" commands complete faster than
 *                          the non-expedited ones, they never block,
 *                          but have the करोwnside of causing extra
 *                          overhead. A process needs to रेजिस्टर its
 *                          पूर्णांकent to use the निजी expedited command
 *                          prior to using it, otherwise this command
 *                          वापसs -EPERM.
 * @MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED:
 *                          Register the process पूर्णांकent to use
 *                          MEMBARRIER_CMD_PRIVATE_EXPEDITED. Always
 *                          वापसs 0.
 * @MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE:
 *                          In addition to provide memory ordering
 *                          guarantees described in
 *                          MEMBARRIER_CMD_PRIVATE_EXPEDITED, ensure
 *                          the caller thपढ़ो, upon वापस from प्रणाली
 *                          call, that all its running thपढ़ोs siblings
 *                          have executed a core serializing
 *                          inकाष्ठाion. (architectures are required to
 *                          guarantee that non-running thपढ़ोs issue
 *                          core serializing inकाष्ठाions beक्रमe they
 *                          resume user-space execution). This only
 *                          covers thपढ़ोs from the same process as the
 *                          caller thपढ़ो. This command वापसs 0 on
 *                          success. The "expedited" commands complete
 *                          faster than the non-expedited ones, they
 *                          never block, but have the करोwnside of
 *                          causing extra overhead. If this command is
 *                          not implemented by an architecture, -EINVAL
 *                          is वापसed. A process needs to रेजिस्टर its
 *                          पूर्णांकent to use the निजी expedited sync
 *                          core command prior to using it, otherwise
 *                          this command वापसs -EPERM.
 * @MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE:
 *                          Register the process पूर्णांकent to use
 *                          MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE.
 *                          If this command is not implemented by an
 *                          architecture, -EINVAL is वापसed.
 *                          Returns 0 on success.
 * @MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ:
 *                          Ensure the caller thपढ़ो, upon वापस from
 *                          प्रणाली call, that all its running thपढ़ो
 *                          siblings have any currently running rseq
 *                          critical sections restarted अगर @flags
 *                          parameter is 0; अगर @flags parameter is
 *                          MEMBARRIER_CMD_FLAG_CPU,
 *                          then this operation is perक्रमmed only
 *                          on CPU indicated by @cpu_id. If this command is
 *                          not implemented by an architecture, -EINVAL
 *                          is वापसed. A process needs to रेजिस्टर its
 *                          पूर्णांकent to use the निजी expedited rseq
 *                          command prior to using it, otherwise
 *                          this command वापसs -EPERM.
 * @MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ:
 *                          Register the process पूर्णांकent to use
 *                          MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ.
 *                          If this command is not implemented by an
 *                          architecture, -EINVAL is वापसed.
 *                          Returns 0 on success.
 * @MEMBARRIER_CMD_SHARED:
 *                          Alias to MEMBARRIER_CMD_GLOBAL. Provided क्रम
 *                          header backward compatibility.
 *
 * Command to be passed to the membarrier प्रणाली call. The commands need to
 * be a single bit each, except क्रम MEMBARRIER_CMD_QUERY which is asचिन्हित to
 * the value 0.
 */
क्रमागत membarrier_cmd अणु
	MEMBARRIER_CMD_QUERY					= 0,
	MEMBARRIER_CMD_GLOBAL					= (1 << 0),
	MEMBARRIER_CMD_GLOBAL_EXPEDITED				= (1 << 1),
	MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED		= (1 << 2),
	MEMBARRIER_CMD_PRIVATE_EXPEDITED			= (1 << 3),
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED		= (1 << 4),
	MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE		= (1 << 5),
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE	= (1 << 6),
	MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ			= (1 << 7),
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ		= (1 << 8),

	/* Alias क्रम header backward compatibility. */
	MEMBARRIER_CMD_SHARED			= MEMBARRIER_CMD_GLOBAL,
पूर्ण;

क्रमागत membarrier_cmd_flag अणु
	MEMBARRIER_CMD_FLAG_CPU		= (1 << 0),
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_MEMBARRIER_H */
