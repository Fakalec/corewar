/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstracke <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 21:01:46 by dstracke          #+#    #+#             */
/*   Updated: 2019/12/16 02:34:38 by dstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define IND_SIZE				2

# define IND_CODE				3
# define DIR_CODE				2
# define REG_CODE				1

# define MAX_PLAYERS			4
# define MAX_ARGS_NUMBER		4

# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define IDX_MOD				(MEM_SIZE / 8)
# define MEM_SIZE				(4*1024)

# define SEPARATOR_CHAR			','
# define DIRECT_CHAR			'%'
# define NAME_CMD_STRING		".name"
# define LABEL_CHAR				':'
# define COMMENT_CMD_STRING		".comment"
# define COMMENT_CHAR			'#'
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define CYCLE_TO_DIE			1536
# define MAX_CHECKS				10
# define REG_NUMBER				16

typedef char	t_arg_type;

# define T_IND					4
# define T_LAB					8
# define T_DIR					2
# define T_REG					1

# define COREWAR_EXEC_MAGIC		0xea83f3
# define COMMENT_LENGTH			(2048)
# define PROG_NAME_LENGTH		(128)

#endif
