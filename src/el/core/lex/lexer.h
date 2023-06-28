#pragma once
#include <memory>
#include <string>

namespace el {
	enum class TokenType {
		kUnknown,
		//symbols
		kComma,					//	,
		kSemicolon,				//	;
		kColon,					//	:
		kLParen,				//	(
		kRParen,				//	)
		kLBrack,				//	[
		kRBrack,				//	]
		kLBrace,				//	{
		kRBrace,				//	}

		//math operators
		kAssign,				// =
		kAdd,					// +
		kSub,					// -
		kMul,					// *
		kDiv,					// /
		kMod,					// %
		kAddAssign,				// +=
		kSubAssign,				// -=
		kMulAssign,				// *=
		kDivAssign,				// /=
		kModAssign,				// %=
		kInc,					// ++
		kDec,					// --

		//bit operators
		kAnd,					// &
		kXor,					// ^
		kOr,					// |
		kInvert,				// ~
		kAndAssign,				//&=
		kXorAssign,				//^=
		kOrAssign,				//|=
		kSHL,					//<<
		kSHR,					//>>

		//logic operators
		kLogicAnd,				//&&
		kLogicOr,				//||
		kLogicNot,				//!
		kLogicEql,				//==
		kLSS,					// <
		kGTR,					// >
		kNEQ,					// !=
		kLEQ,					// <=
		kGEQ,					// >=

		//constant number
		kInteger,				//constant number 123123
		kFloat,					//constant float number 1.123 1.0f

		//constant string and character
		kCharacter,				//'a'
		kString,				//"aaa"

		//keyword
		kWorkdInt,				//int
		kWordInt8,				//int8
		kWordInt16,				//int16
		kWordInt32,				//int32
		kWordInt64,				//int64
		kWordUint8,				//uint8
		kWordUint16,			//uint32
		kWordUint32,			//uint32
		kWordUint64,			//uint64
		kWordFloat,				//float
		kWordFloat32,			//float32
		kWordFloat64,			//float64
		kWordBool,				//bool
		kWordString,			//string
		kWordByte,				//byte
		kWordAuto,				//auto
		kWordAny,				//any
		kWordNull,				//null
		kWordError,				//error,
	};

	struct Token {
		TokenType type{ TokenType::kUnknown };
		std::uint64_t line;
		std::uint64_t offest{ 0 };
		std::string value;
	};

	class Lexer {
	public:
		static bool Parse(
			const std::string& source);

	};
}