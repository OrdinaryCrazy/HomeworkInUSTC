// Generated from C1Parser.g4 by ANTLR 4.7.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link C1Parser}.
 */
public interface C1ParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link C1Parser#compilationUnit}.
	 * @param ctx the parse tree
	 */
	void enterCompilationUnit(C1Parser.CompilationUnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#compilationUnit}.
	 * @param ctx the parse tree
	 */
	void exitCompilationUnit(C1Parser.CompilationUnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#declorfuncdef}.
	 * @param ctx the parse tree
	 */
	void enterDeclorfuncdef(C1Parser.DeclorfuncdefContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#declorfuncdef}.
	 * @param ctx the parse tree
	 */
	void exitDeclorfuncdef(C1Parser.DeclorfuncdefContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#decl}.
	 * @param ctx the parse tree
	 */
	void enterDecl(C1Parser.DeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#decl}.
	 * @param ctx the parse tree
	 */
	void exitDecl(C1Parser.DeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#constdecl}.
	 * @param ctx the parse tree
	 */
	void enterConstdecl(C1Parser.ConstdeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#constdecl}.
	 * @param ctx the parse tree
	 */
	void exitConstdecl(C1Parser.ConstdeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#btype}.
	 * @param ctx the parse tree
	 */
	void enterBtype(C1Parser.BtypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#btype}.
	 * @param ctx the parse tree
	 */
	void exitBtype(C1Parser.BtypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#constdef}.
	 * @param ctx the parse tree
	 */
	void enterConstdef(C1Parser.ConstdefContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#constdef}.
	 * @param ctx the parse tree
	 */
	void exitConstdef(C1Parser.ConstdefContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#vardecl}.
	 * @param ctx the parse tree
	 */
	void enterVardecl(C1Parser.VardeclContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#vardecl}.
	 * @param ctx the parse tree
	 */
	void exitVardecl(C1Parser.VardeclContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#vardef}.
	 * @param ctx the parse tree
	 */
	void enterVardef(C1Parser.VardefContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#vardef}.
	 * @param ctx the parse tree
	 */
	void exitVardef(C1Parser.VardefContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#funcdef}.
	 * @param ctx the parse tree
	 */
	void enterFuncdef(C1Parser.FuncdefContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#funcdef}.
	 * @param ctx the parse tree
	 */
	void exitFuncdef(C1Parser.FuncdefContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(C1Parser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(C1Parser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#blockitem}.
	 * @param ctx the parse tree
	 */
	void enterBlockitem(C1Parser.BlockitemContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#blockitem}.
	 * @param ctx the parse tree
	 */
	void exitBlockitem(C1Parser.BlockitemContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(C1Parser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(C1Parser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#lval}.
	 * @param ctx the parse tree
	 */
	void enterLval(C1Parser.LvalContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#lval}.
	 * @param ctx the parse tree
	 */
	void exitLval(C1Parser.LvalContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#cond}.
	 * @param ctx the parse tree
	 */
	void enterCond(C1Parser.CondContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#cond}.
	 * @param ctx the parse tree
	 */
	void exitCond(C1Parser.CondContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#relop}.
	 * @param ctx the parse tree
	 */
	void enterRelop(C1Parser.RelopContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#relop}.
	 * @param ctx the parse tree
	 */
	void exitRelop(C1Parser.RelopContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#exp}.
	 * @param ctx the parse tree
	 */
	void enterExp(C1Parser.ExpContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#exp}.
	 * @param ctx the parse tree
	 */
	void exitExp(C1Parser.ExpContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#number}.
	 * @param ctx the parse tree
	 */
	void enterNumber(C1Parser.NumberContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#number}.
	 * @param ctx the parse tree
	 */
	void exitNumber(C1Parser.NumberContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#binop}.
	 * @param ctx the parse tree
	 */
	void enterBinop(C1Parser.BinopContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#binop}.
	 * @param ctx the parse tree
	 */
	void exitBinop(C1Parser.BinopContext ctx);
	/**
	 * Enter a parse tree produced by {@link C1Parser#unaryop}.
	 * @param ctx the parse tree
	 */
	void enterUnaryop(C1Parser.UnaryopContext ctx);
	/**
	 * Exit a parse tree produced by {@link C1Parser#unaryop}.
	 * @param ctx the parse tree
	 */
	void exitUnaryop(C1Parser.UnaryopContext ctx);
}