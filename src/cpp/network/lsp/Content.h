//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                <https://github.com/casm-lang/libstdhl>
//
//  This file is part of libstdhl.
//
//  libstdhl is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libstdhl is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libstdhl. If not, see <http://www.gnu.org/licenses/>.
//
//  Additional permission under GNU GPL version 3 section 7
//
//  libstdhl is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libstdhl
//  statically or dynamically with other modules is making a combined work
//  based on libstdhl. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libstdhl give you permission to link libstdhl
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libstdhl. If you modify libstdhl, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#pragma once
#ifndef _LIBSTDHL_CPP_NETWORK_LSP_CONTENT_H_
#define _LIBSTDHL_CPP_NETWORK_LSP_CONTENT_H_

#include <libstdhl/json/Json>
#include <libstdhl/standard/rfc3986>
#include <libstdhl/type/Type>

/**
   @brief    TBD

   TBD

   https://github.com/Microsoft/language-server-protocol/blob/master/protocol.md
*/

namespace libstdhl
{
    namespace Network
    {
        namespace LSP
        {
            using Data = libstdhl::Json::Object;

            using DocumentUri = libstdhl::Standard::RFC3986::URI;

            enum class ErrorCode : i32
            {
                // defined by JSON RPC
                ParseError = -32700,
                InvalidRequest = -32600,
                MethodNotFound = -32601,
                InvalidParams = -32602,
                InternalError = -32603,
                serverErrorStart = -32099,
                serverErrorEnd = -32000,
                ServerNotInitialized = -32002,
                UnknownErrorCode = -32001,

                // defined by LSP
                RequestCancelled = -32800,

            };

            class ResponseError final : public Data
            {
              public:
                ResponseError( const Data& data );

                ResponseError( const ErrorCode code, const std::string& message );

                ErrorCode code( void ) const;

                std::string message( void ) const;

                u1 hasData( void ) const;

                Data data( void ) const;

                void setData( const Data& data );

                static u1 isValid( const Data& data );
            };

            namespace TextDocument
            {
                constexpr const std::array< const char*, 3 > EOL = { { "\n", "\r\n", "\r" } };
            }

            class Position : public Data
            {
              public:
                Position( const Data& data );

                Position( const std::size_t line, const std::size_t character );

                std::size_t line( void ) const;

                std::size_t character( void ) const;

                static u1 isValid( const Data& data );
            };

            class Range : public Data
            {
              public:
                Range( const Data& data );

                Range( const Position& start, const Position& end );

                Position start( void ) const;

                Position end( void ) const;

                static u1 isValid( const Data& data );
            };

            class Location : public Data
            {
              public:
                Location( const Data& data );

                Location( const DocumentUri& uri, const Range& range );

                DocumentUri uri( void ) const;

                Range range( void ) const;

                static u1 isValid( const Data& data );
            };

            enum class DiagnosticSeverity : std::size_t
            {
                Error = 1,
                Warning = 2,
                Information = 3,
                Hint = 4,
            };

            class Diagnostic : public Data
            {
              public:
                Diagnostic( const Data& data );

                Diagnostic( const Range& range, const std::string& message );

                Range range( void ) const;

                std::string message( void ) const;

                u1 hasSeverity( void ) const;

                DiagnosticSeverity severity( void ) const;

                void setSeverity( const DiagnosticSeverity& severity );

                u1 hasCode( void ) const;

                std::string code( void ) const;

                void setCode( const std::string& code );

                void setCode( const std::size_t code );

                u1 hasSource( void ) const;

                std::string source( void ) const;

                void setSource( const std::string& source );

                static u1 isValid( const Data& data );
            };

            class Command : public Data
            {
              public:
                Command( const Data& data );

                Command( const std::string& title, const std::string& command );

                std::string title( void ) const;

                std::string command( void ) const;

                u1 hasArguments( void ) const;

                Data arguments( void ) const;

                void addArgument( const Data& argument );

                static u1 isValid( const Data& data );
            };

            class TextEdit : public Data
            {
              public:
                TextEdit( const Data& data );

                TextEdit( const Range& range, const std::string newText );

                Range range( void ) const;

                std::string newText( void ) const;

                static u1 isValid( const Data& data );
            };

            class TextDocumentIdentifier : public Data
            {
              public:
                TextDocumentIdentifier( const Data& data );

                TextDocumentIdentifier( const DocumentUri& uri );

                DocumentUri uri( void ) const;

                static u1 isValid( const Data& data );
            };

            class VersionedTextDocumentIdentifier : public TextDocumentIdentifier
            {
              public:
                VersionedTextDocumentIdentifier( const Data& data );

                VersionedTextDocumentIdentifier(
                    const DocumentUri& uri, const std::size_t version );

                std::size_t version( void ) const;

                static u1 isValid( const Data& data );
            };

            class TextDocumentEdit : public Data
            {
              public:
                TextDocumentEdit( const Data& data );

                TextDocumentEdit(
                    const VersionedTextDocumentIdentifier& textDocument,
                    const std::vector< TextEdit >& edits );

                VersionedTextDocumentIdentifier textDocument( void ) const;

                Data edits( void ) const;

                static u1 isValid( const Data& data );
            };

            class WorkspaceEdit : public Data
            {
              public:
                WorkspaceEdit( const Data& data );

                WorkspaceEdit( void );

                // changes interface omitted!

                u1 hasDocumentChanges( void ) const;

                Data documentChanges( void ) const;

                void addDocumentChange( const TextDocumentEdit& documentChange );

                static u1 isValid( const Data& data );
            };

            class TextDocumentItem : public Data
            {
              public:
                TextDocumentItem( const Data& data );

                TextDocumentItem(
                    const DocumentUri& uri,
                    const std::string& languageId,
                    const std::size_t version,
                    const std::string& text );

                DocumentUri uri( void ) const;

                std::string languageId( void ) const;

                std::size_t version( void ) const;

                std::string text( void ) const;

                static u1 isValid( const Data& data );
            };

            class TextDocumentPositionParams : public Data
            {
              public:
                TextDocumentPositionParams( const Data& data );

                TextDocumentPositionParams(
                    const TextDocumentIdentifier& textDocument, const Position& position );

                TextDocumentIdentifier textDocument( void ) const;

                Position position( void ) const;

                static u1 isValid( const Data& data );
            };

            class DocumentFilter : public Data
            {
              public:
                DocumentFilter( const Data& data );

                DocumentFilter( void );

                u1 hasLanguage( void ) const;

                std::string language( void ) const;

                void setLanguage( const std::string& language );

                u1 hasScheme( void ) const;

                std::string scheme( void ) const;

                void setScheme( const std::string& scheme );

                u1 hasPattern( void ) const;

                std::string pattern( void ) const;

                void setPattern( const std::string& pattern );

                static u1 isValid( const Data& data );
            };

            class DocumentSelector : public Data
            {
              public:
                DocumentSelector( const Data& data );

                DocumentSelector( const std::vector< DocumentFilter >& documentFilters );

                static u1 isValid( const Data& data );
            };

            //
            //
            // Actual Protocol
            //

            class DynamicRegistration : public Data
            {
              public:
                DynamicRegistration( const Data& data );

                DynamicRegistration( void );

                u1 hasDynamicRegistration( void ) const;

                u1 dynamicRegistration( void ) const;

                void setDynamicRegistration( const u1 dynamicRegistration );

                static u1 isValid( const Data& data );
            };

            class WorkspaceClientCapabilities : public Data
            {
              public:
                WorkspaceClientCapabilities( const Data& data );

                WorkspaceClientCapabilities( void );

                u1 hasApplyEdit( void ) const;

                u1 applyEdit( void ) const;

                void setApplyEdit( const u1 applyEdit );

                u1 hasWorkspaceEdit( void ) const;

                WorkspaceEdit workspaceEdit( void ) const;

                void setWorkspaceEdit( const WorkspaceEdit& workspaceEdit );

                u1 hasDidChangeConfiguration( void ) const;

                DynamicRegistration didChangeConfiguration( void ) const;

                void setDidChangeConfiguration( const DynamicRegistration& didChangeConfiguration );

                u1 hasDidChangeWatchedFiles( void ) const;

                DynamicRegistration didChangeWatchedFiles( void ) const;

                void didChangeWatchedFiles( const DynamicRegistration& didChangeWatchedFiles );

                u1 hasSymbol( void ) const;

                DynamicRegistration symbol( void ) const;

                void setSymbol( const DynamicRegistration& symbol );

                u1 hasExecuteCommand( void ) const;

                DynamicRegistration executeCommand( void ) const;

                void executeCommand( const DynamicRegistration& executeCommand );

                static u1 isValid( const Data& data );
            };

            class Synchronization : public Data
            {
              public:
                Synchronization( const Data& data );

                Synchronization( void );

                u1 hasDynamicRegistration( void ) const;

                u1 dynamicRegistration( void ) const;

                void setDynamicRegistration( const u1 dynamicRegistration );

                u1 hasWillSave( void ) const;

                u1 willSave( void ) const;

                void setWillSave( const u1 willSave );

                u1 hasWillSaveWaitUntil( void ) const;

                u1 willSaveWaitUntil( void ) const;

                void setWillSaveWaitUntil( const u1 willSaveWaitUntil );

                u1 hasDidSave( void ) const;

                u1 didSave( void ) const;

                void setDidSave( const u1 didSave );

                static u1 isValid( const Data& data );
            };

            class CompletionItem : public Data
            {
              public:
                CompletionItem( const Data& data );

                CompletionItem( void );

                u1 hasSnippetSupport( void ) const;

                u1 snippetSupport( void ) const;

                void setSnippetSupport( const u1 snippetSupport );

                static u1 isValid( const Data& data );
            };

            class Completion : public Data
            {
              public:
                Completion( const Data& data );

                Completion( void );

                u1 hasDynamicRegistration( void ) const;

                u1 dynamicRegistration( void ) const;

                void setDynamicRegistration( const u1 dynamicRegistration );

                u1 hasCompletionItem( void ) const;

                CompletionItem completionItem( void ) const;

                void completionItem( const CompletionItem& completionItem );

                static u1 isValid( const Data& data );
            };

            class TextDocumentClientCapabilities : public Data
            {
              public:
                TextDocumentClientCapabilities( const Data& data );

                TextDocumentClientCapabilities( void );

                u1 hasSynchronization( void ) const;

                Synchronization synchronization( void ) const;

                void setSynchronization( const Synchronization& synchronization );

                u1 hasCompletion( void ) const;

                Completion completion( void ) const;

                void setCompletion( const Completion& completion );

                u1 hasHover( void ) const;

                DynamicRegistration hover( void ) const;

                void setHover( const DynamicRegistration& hover );

                u1 hasSignatureHelp( void ) const;

                DynamicRegistration signatureHelp( void ) const;

                void setSignatureHelp( const DynamicRegistration& signatureHelp );

                u1 hasReferences( void ) const;

                DynamicRegistration references( void ) const;

                void setReferences( const DynamicRegistration& references );

                u1 hasDocumentHighlight( void ) const;

                DynamicRegistration documentHighlight( void ) const;

                void setDocumentHighlight( const DynamicRegistration& documentHighlight );

                u1 hasDocumentSymbol( void ) const;

                DynamicRegistration documentSymbol( void ) const;

                void setDocumentSymbol( const DynamicRegistration& documentSymbol );

                u1 hasFormatting( void ) const;

                DynamicRegistration formatting( void ) const;

                void setFormatting( const DynamicRegistration& formatting );

                u1 hasRangeFormatting( void ) const;

                DynamicRegistration rangeFormatting( void ) const;

                void setRangeFormatting( const DynamicRegistration& rangeFormatting );

                u1 hasOnTypeFormatting( void ) const;

                DynamicRegistration onTypeFormatting( void ) const;

                void setOnTypeFormatting( const DynamicRegistration& onTypeFormatting );

                u1 hasDefinition( void ) const;

                DynamicRegistration definition( void ) const;

                void setDefinition( const DynamicRegistration& definition );

                u1 hasCodeAction( void ) const;

                DynamicRegistration codeAction( void ) const;

                void setCodeAction( const DynamicRegistration& codeAction );

                u1 hasCodeLens( void ) const;

                DynamicRegistration codeLens( void ) const;

                void setCodeLens( const DynamicRegistration& codeLens );

                u1 hasDocumentLink( void ) const;

                DynamicRegistration documentLink( void ) const;

                void setDocumentLink( const DynamicRegistration& documentLink );

                u1 hasRename( void ) const;

                DynamicRegistration rename( void ) const;

                void setRename( const DynamicRegistration& rename );

                static u1 isValid( const Data& data );
            };

            class ClientCapabilities : public Data
            {
              public:
                ClientCapabilities( const Data& data );

                ClientCapabilities( void );

                u1 hasWorkspace( void ) const;

                WorkspaceClientCapabilities workspace( void ) const;

                void setWorkspace( const WorkspaceClientCapabilities& workspace );

                u1 hasTextDocument( void ) const;

                TextDocumentClientCapabilities textDocument( void ) const;

                void setTextDocument( const TextDocumentClientCapabilities& textDocument );

                u1 hasExperimental( void ) const;

                Data experimental( void ) const;

                void setExperimental( const Data& experimental );

                static u1 isValid( const Data& data );
            };

            class SaveOptions : public Data
            {
              public:
                SaveOptions( const Data& data );

                SaveOptions( void );

                u1 hasIncludeText( void ) const;

                u1 includeText( void ) const;

                void setIncludeText( const u1 includeText );

                static u1 isValid( const Data& data );
            };

            enum class TextDocumentSyncKind
            {
                None = 0,
                Full = 1,
                Incremental = 2,
            };

            class TextDocumentSyncOptions : public Data
            {
              public:
                TextDocumentSyncOptions( const Data& data );

                TextDocumentSyncOptions( void );

                u1 hasOpenClose( void ) const;

                u1 openClose( void ) const;

                void setOpenClose( const u1 openClose );

                u1 hasChange( void ) const;

                TextDocumentSyncKind change( void ) const;

                void setChange( const TextDocumentSyncKind& change );

                u1 hasWillSave( void ) const;

                u1 willSave( void ) const;

                void setWillSave( const u1 willSave );

                u1 hasWillSaveWaitUntil( void ) const;

                u1 willSaveWaitUntil( void ) const;

                void setWillSaveWaitUntil( const u1 willSaveWaitUntil );

                u1 hasSave( void ) const;

                SaveOptions save( void ) const;

                void setSave( const SaveOptions& save );

                static u1 isValid( const Data& data );
            };

            class CompletionOptions : public Data
            {
              public:
                CompletionOptions( const Data& data );

                CompletionOptions( void );

                u1 hasResolveProvider( void ) const;

                u1 resolveProvider( void ) const;

                void setResolveProvider( const u1 resolveProvider );

                u1 hasTriggerCharacters( void ) const;

                Data triggerCharacters( void ) const;

                void addTriggerCharacters( const std::string& triggerCharacter );

                static u1 isValid( const Data& data );
            };

            class SignatureHelpOptions : public Data
            {
              public:
                SignatureHelpOptions( const Data& data );

                SignatureHelpOptions( void );

                u1 hasTriggerCharacters( void ) const;

                Data triggerCharacters( void ) const;

                void addTriggerCharacters( const std::string& triggerCharacter );

                static u1 isValid( const Data& data );
            };

            class CodeLensOptions : public Data
            {
              public:
                CodeLensOptions( const Data& data );

                CodeLensOptions( void );

                u1 hasResolveProvider( void ) const;

                u1 resolveProvider( void ) const;

                void setResolveProvider( const u1 resolveProvider );

                static u1 isValid( const Data& data );
            };

            class DocumentOnTypeFormattingOptions : public Data
            {
              public:
                DocumentOnTypeFormattingOptions( const Data& data );

                DocumentOnTypeFormattingOptions( const std::string& firstTriggerCharacter );

                std::string firstTriggerCharacter( void ) const;

                u1 hasMoreTriggerCharacter( void ) const;

                Data moreTriggerCharacter( void ) const;

                void addMoreTriggerCharacter( const Data& moreTriggerCharacter );

                static u1 isValid( const Data& data );
            };

            using DocumentLinkOptions = CodeLensOptions;

            class ExecuteCommandOptions : public Data
            {
              public:
                ExecuteCommandOptions( const Data& data );

                ExecuteCommandOptions( void );

                u1 hasCommands( void ) const;

                Data commands( void ) const;

                void addCommand( const std::string& command );

                static u1 isValid( const Data& data );
            };

            class ServerCapabilities : public Data
            {
              public:
                ServerCapabilities( const Data& data );

                ServerCapabilities( void );

                u1 hasTextDocumentSync( void ) const;

                TextDocumentSyncOptions textDocumentSync( void ) const;

                void setTextDocumentSync( const TextDocumentSyncOptions& textDocumentSync );

                void setTextDocumentSync( const TextDocumentSyncKind& textDocumentSync );

                u1 hasHoverProvider( void ) const;

                u1 hoverProvider( void ) const;

                void setHoverProvider( const u1 hoverProvider );

                u1 hasCompletionProvider( void ) const;

                CompletionOptions completionProvider( void ) const;

                void setCompletionProvider( const CompletionOptions& completionProvider );

                u1 hasSignatureHelpProvider( void ) const;

                SignatureHelpOptions signatureHelpProvider( void ) const;

                void setSignatureHelpProvider( const SignatureHelpOptions& signatureHelpProvider );

                u1 hasDefinitionProvider( void ) const;

                u1 definitionProvider( void ) const;

                void setDefinitionProvider( const u1 definitionProvider );

                u1 hasReferencesProvider( void ) const;

                u1 referencesProvider( void ) const;

                void setReferencesProvider( const u1 referencesProvider );

                u1 hasDocumentHighlightProvider( void ) const;

                u1 documentHighlightProvider( void ) const;

                void setDocumentHighlightProvider( const u1 documentHighlightProvider );

                u1 hasDocumentSymbolProvider( void ) const;

                u1 documentSymbolProvider( void ) const;

                void setDocumentSymbolProvider( const u1 documentSymbolProvider );

                u1 hasWorkspaceSymbolProvider( void ) const;

                u1 workspaceSymbolProvider( void ) const;

                void setWorkspaceSymbolProvider( const u1 workspaceSymbolProvider );

                u1 hasCodeActionProvider( void ) const;

                u1 codeActionProvider( void ) const;

                void setCodeActionProvider( const u1 codeActionProvider );

                u1 hasCodeLensProvider( void ) const;

                CodeLensOptions codeLensProvider( void ) const;

                void setCodeLensProvider( const CodeLensOptions& codeLensProvider );

                u1 hasDocumentFormattingProvider( void ) const;

                u1 documentFormattingProvider( void ) const;

                void setDocumentFormattingProvider( const u1 documentFormattingProvider );

                u1 hasDocumentRangeFormattingProvider( void ) const;

                u1 documentRangeFormattingProvider( void ) const;

                void setDocumentRangeFormattingProvider( const u1 documentRangeFormattingProvider );

                u1 hasDocumentOnTypeFormattingProvider( void ) const;

                DocumentOnTypeFormattingOptions documentOnTypeFormattingProvider( void ) const;

                void setDocumentOnTypeFormattingProvider(
                    const DocumentOnTypeFormattingOptions& documentOnTypeFormattingProvider );

                u1 hasRenameProvider( void ) const;

                u1 renameProvider( void ) const;

                void setRenameProvider( const u1 renameProvider );

                u1 hasDocumentLinkProvider( void ) const;

                DocumentLinkOptions documentLinkProvider( void ) const;

                void setDocumentLinkProvider( const DocumentLinkOptions& documentLinkProvider );

                u1 hasExecuteCommandProvider( void ) const;

                ExecuteCommandOptions executeCommandProvider( void ) const;

                void setExecuteCommandProvider(
                    const ExecuteCommandOptions& executeCommandProvider );

                u1 hasExperimental( void ) const;

                Data experimental( void ) const;

                void setExperimental( const Data& experimental );

                static u1 isValid( const Data& data );
            };

            class InitializeParams : public Data
            {
              public:
                InitializeParams( const Data& data );

                InitializeParams(
                    const std::size_t processId,
                    const DocumentUri& rootUri,
                    const ClientCapabilities& capabilities );

                std::size_t processId( void ) const;

                // rootPath interface omitted!

                DocumentUri rootUri( void ) const;

                u1 hasInitializationOptions( void ) const;

                Data initializationOptions( void ) const;

                void setInitializationOptions( const Data& initializationOptions );

                ClientCapabilities capabilities( void ) const;

                u1 hasTrace( void ) const;

                std::string trace( void ) const;

                void setTrace( const std::string& trace );

                static u1 isValid( const Data& data );
            };

            class InitializeResult : public Data
            {
              public:
                InitializeResult( const Data& data );

                InitializeResult( const ServerCapabilities& capabilities );

                ServerCapabilities capabilities( void ) const;

                static u1 isValid( const Data& data );
            };

            class InitializeError : public Data
            {
              public:
                InitializeError( const Data& data );

                InitializeError( const u1 retry );

                u1 retry( void ) const;

                static u1 isValid( const Data& data );
            };

            class DidOpenTextDocumentParams : public Data
            {
              public:
                DidOpenTextDocumentParams( const Data& data );

                DidOpenTextDocumentParams( const TextDocumentItem& textDocument );

                TextDocumentItem textDocument( void ) const;

                static u1 isValid( const Data& data );
            };

            class TextDocumentContentChangeEvent : public Data
            {
              public:
                TextDocumentContentChangeEvent( const Data& data );

                TextDocumentContentChangeEvent( const std::string& text );

                u1 hasRange( void ) const;

                Range range( void ) const;

                void setRange( const Range& range );

                u1 hasRangeLength( void ) const;

                std::size_t rangeLength( void ) const;

                void setRangeLength( const std::size_t rangeLength );

                std::string text( void ) const;

                static u1 isValid( const Data& data );
            };

            class DidChangeTextDocumentParams : public Data
            {
              public:
                DidChangeTextDocumentParams( const Data& data );

                DidChangeTextDocumentParams(
                    const VersionedTextDocumentIdentifier& textDocument,
                    const std::vector< TextDocumentContentChangeEvent >& contentChanges );

                VersionedTextDocumentIdentifier textDocument( void ) const;

                Data contentChanges( void ) const;

                static u1 isValid( const Data& data );
            };

            class CodeActionContext : public Data
            {
              public:
                CodeActionContext( const Data& data );

                CodeActionContext( const std::vector< Diagnostic >& diagnostics );

                Data diagnostics( void ) const;

                static u1 isValid( const Data& data );
            };

            class CodeActionParams : public Data
            {
              public:
                CodeActionParams( const Data& data );

                CodeActionParams(
                    const TextDocumentIdentifier& textDocument,
                    const Range& range,
                    const CodeActionContext& context );

                TextDocumentIdentifier textDocument( void ) const;

                Range range( void ) const;

                CodeActionContext context( void ) const;

                static u1 isValid( const Data& data );
            };

            class CodeActionResult : public Data
            {
              public:
                CodeActionResult( const Data& data );

                CodeActionResult( const std::vector< Command >& commands );

                CodeActionResult( void );

                void addCommand( const Command& command );

                static u1 isValid( const Data& data );
            };

            class PublishDiagnosticsParams : public Data
            {
              public:
                PublishDiagnosticsParams( const Data& data );

                PublishDiagnosticsParams(
                    const DocumentUri& uri, const std::vector< Diagnostic >& diagnostics );

                DocumentUri uri( void ) const;

                Data diagnostics( void ) const;

                static u1 isValid( const Data& data );
            };

            using HoverParams = TextDocumentPositionParams;

            class MarkedString : public Data
            {
              public:
                MarkedString( const Data& data );

                MarkedString( const std::string& language, const std::string& value );

                std::string language( void ) const;

                std::string value( void ) const;

                static u1 isValid( const Data& data );
            };

            class HoverResult : public Data
            {
              public:
                HoverResult( const Data& data );

                HoverResult( const std::vector< MarkedString >& contents = {} );

                Data contents( void ) const;

                void addContent( const MarkedString& content );

                u1 hasRange( void ) const;

                Range range( void ) const;

                void setRange( const Range& range );

                static u1 isValid( const Data& data );
            };

            class CodeLensParams : public Data
            {
              public:
                CodeLensParams( const Data& data );

                CodeLensParams( const TextDocumentIdentifier& textDocument );

                TextDocumentIdentifier textDocument( void ) const;

                static u1 isValid( const Data& data );
            };

            class CodeLens : public Data
            {
              public:
                CodeLens( const Data& data );

                CodeLens( const Range& range );

                Range range( void ) const;

                u1 hasCommand( void ) const;

                Command command( void ) const;

                void setCommand( const Command& command );

                u1 hasData( void ) const;

                Data data( void ) const;

                void setData( const Data& data );

                static u1 isValid( const Data& data );
            };

            class CodeLensResult : public Data
            {
              public:
                CodeLensResult( const Data& data );

                CodeLensResult( const std::vector< CodeLens >& codeLens = {} );

                void addCodeLens( const CodeLens& codeLens );

                static u1 isValid( const Data& data );
            };

            class ExecuteCommandParams : public Data
            {
              public:
                ExecuteCommandParams( const Data& data );

                ExecuteCommandParams( const std::string& command );

                std::string command( void ) const;

                u1 hasArguments( void ) const;

                Data arguments( void ) const;

                void addArgument( const Data& argument );

                static u1 isValid( const Data& data );
            };

            using ExecuteCommandResult = Data;  // TODO: PPA: FIXME:
        }
    }
}

#endif  // _LIBSTDHL_CPP_NETWORK_LSP_CONTENT_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
